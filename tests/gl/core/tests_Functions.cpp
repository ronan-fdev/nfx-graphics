#include <doctest/doctest.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <map>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace
{
    namespace fs = std::filesystem;

    fs::path repoRoot()
    {
        // .../tests/gl/core/Functions.cpp -> repo root is 4 levels up
        fs::path p{ __FILE__ };
        return p.parent_path().parent_path().parent_path().parent_path();
    }

    std::vector<fs::path> functionCppFiles()
    {
        const fs::path dir = repoRoot() / "src" / "gl" / "core" / "functions";
        std::vector<fs::path> files;

        const std::regex namePattern(R"(^Functions_\d_\d\.cpp$)");
        for (const auto& entry : fs::directory_iterator(dir))
        {
            if (!entry.is_regular_file())
            {
                continue;
            }

            const std::string name = entry.path().filename().string();
            if (std::regex_match(name, namePattern))
            {
                files.push_back(entry.path());
            }
        }

        std::sort(files.begin(), files.end());
        return files;
    }

    bool hasBindingSourceFiles()
    {
        const fs::path functionsDir = repoRoot() / "src" / "gl" / "core" / "functions";
        const fs::path pointersFile =
            repoRoot() / "src" / "gl" / "core" / "functions" / "loader" / "FunctionPointers.h";

        if (!fs::exists(functionsDir) || !fs::exists(pointersFile))
        {
            return false;
        }

        const auto files = functionCppFiles();
        return !files.empty();
    }

    std::string readText(const fs::path& p)
    {
        std::ifstream in(p);
        if (!in.good())
        {
            INFO("Cannot open file: " << p.string());
            REQUIRE(in.good());
        }
        std::ostringstream ss;
        ss << in.rdbuf();
        return ss.str();
    }

    std::vector<std::string> splitLines(const std::string& text)
    {
        std::vector<std::string> lines;
        std::istringstream is(text);
        std::string line;
        while (std::getline(is, line))
        {
            lines.push_back(line);
        }
        return lines;
    }

    std::set<std::string> loadedFunctionNames()
    {
        const std::regex loadPattern(R"re(loadFunctionPtr\("(gl[A-Za-z0-9_]+)"\))re");
        std::set<std::string> loaded;

        for (const auto& file : functionCppFiles())
        {
            const auto lines = splitLines(readText(file));
            for (const auto& line : lines)
            {
                std::smatch match;
                if (std::regex_search(line, match, loadPattern))
                {
                    loaded.insert(match[1].str());
                }
            }
        }

        return loaded;
    }

    std::map<std::string, std::vector<std::string>> declaredPointersByVersion()
    {
        const auto lines =
            splitLines(readText(repoRoot() / "src" / "gl" / "core" / "functions" / "loader" / "FunctionPointers.h"));
        const std::regex versionPattern(R"(/\* OPENGL_VERSION_(\d_\d) \*/)");
        const std::regex pointerPattern(R"(_nfx_(gl[A-Za-z0-9_]+)\b)");

        std::map<std::string, std::vector<std::string>> declared;
        std::string currentVersion;

        for (const auto& line : lines)
        {
            std::smatch versionMatch;
            if (std::regex_search(line, versionMatch, versionPattern))
            {
                currentVersion = versionMatch[1].str();
                continue;
            }

            std::smatch pointerMatch;
            if (!currentVersion.empty() && std::regex_search(line, pointerMatch, pointerPattern))
            {
                declared[currentVersion].push_back(pointerMatch[1].str());
            }
        }

        return declared;
    }
} // namespace

TEST_SUITE("FunctionLoader - Binding Verification")
{
    TEST_CASE("All initialize bindings map _nfx_glX -> loadFunctionPtr(\"glX\")")
    {
        if (!hasBindingSourceFiles())
        {
            INFO("Skipping: source files are not available in standalone binary mode.");
            return;
        }

        const std::regex lhsPattern(R"(_nfx_(gl[A-Za-z0-9_]+)\s*=)");
        const std::regex rhsPattern(R"re(loadFunctionPtr\("(gl[A-Za-z0-9_]+)"\))re");

        int totalChecked = 0;
        std::vector<std::string> mismatches;

        for (const auto& file : functionCppFiles())
        {
            const auto lines = splitLines(readText(file));
            for (size_t i = 0; i < lines.size(); ++i)
            {
                std::smatch lhsMatch;
                if (!std::regex_search(lines[i], lhsMatch, lhsPattern))
                {
                    continue;
                }

                // Read the full assignment statement up to ';' across multiple lines
                std::string statement = lines[i];
                size_t j = i;
                while (statement.find(';') == std::string::npos && (j + 1) < lines.size())
                {
                    ++j;
                    statement += "\n" + lines[j];
                }

                std::smatch rhsMatch;
                if (!std::regex_search(statement, rhsMatch, rhsPattern))
                {
                    continue;
                }

                const std::string lhs = lhsMatch[1].str();
                const std::string rhs = rhsMatch[1].str();
                ++totalChecked;

                if (lhs != rhs)
                {
                    mismatches.push_back(
                        file.filename().string() + ": _nfx_" + lhs + " <- loadFunctionPtr(\"" + rhs + "\")");
                }
            }
        }

        INFO("Total checked bindings: " << totalChecked);
        CHECK(totalChecked > 0);
        if (!mismatches.empty())
        {
            std::ostringstream os;
            os << "Binding mismatches found:\n";
            for (const auto& m : mismatches)
            {
                os << " - " << m << "\n";
            }
            FAIL_CHECK(os.str());
        }
    }

    TEST_CASE("All declared 1.2+ pointers are loaded")
    {
        if (!hasBindingSourceFiles())
        {
            INFO("Skipping: source files are not available in standalone binary mode.");
            return;
        }

        const auto declared = declaredPointersByVersion();
        const auto loaded = loadedFunctionNames();
        std::vector<std::string> missing;

        for (const auto& [version, names] : declared)
        {
            if (version == "1_0" || version == "1_1")
            {
                continue;
            }

            for (const auto& name : names)
            {
                if (!loaded.contains(name))
                {
                    missing.push_back(version + ": " + name);
                }
            }
        }

        INFO("Total loaded dynamic functions: " << loaded.size());
        if (!missing.empty())
        {
            std::ostringstream os;
            os << "Declared pointers missing loadFunctionPtr bindings:\n";
            for (const auto& item : missing)
            {
                os << " - " << item << "\n";
            }
            FAIL_CHECK(os.str());
        }

        CHECK(missing.empty());
    }

    TEST_CASE("All wrapper methods call matching _nfx pointer")
    {
        if (!hasBindingSourceFiles())
        {
            INFO("Skipping: source files are not available in standalone binary mode.");
            return;
        }

        const std::regex fnPattern(R"(Functions_\d_\d::(gl[A-Za-z0-9_]+)\s*\()");
        const std::regex ptrPattern(R"(_nfx_(gl[A-Za-z0-9_]+)\s*\()");

        int totalWrappers = 0;
        int totalChecked = 0;
        int totalSkipped = 0;
        std::vector<std::string> mismatches;
        std::vector<std::string> skippedWrappers;

        for (const auto& file : functionCppFiles())
        {
            const std::string text = readText(file);

            auto it = std::sregex_iterator(text.begin(), text.end(), fnPattern);
            const auto end = std::sregex_iterator();
            for (; it != end; ++it)
            {
                ++totalWrappers;
                const std::string methodName = (*it)[1].str();
                const size_t fnPos = static_cast<size_t>((*it).position());

                const size_t bodyStart = text.find('{', fnPos);
                if (bodyStart == std::string::npos)
                {
                    continue;
                }

                int depth = 0;
                size_t bodyEnd = bodyStart;
                for (; bodyEnd < text.size(); ++bodyEnd)
                {
                    if (text[bodyEnd] == '{')
                    {
                        ++depth;
                    }
                    else if (text[bodyEnd] == '}')
                    {
                        --depth;
                        if (depth == 0)
                        {
                            break;
                        }
                    }
                }

                if (bodyEnd <= bodyStart)
                {
                    continue;
                }

                const std::string body = text.substr(bodyStart, bodyEnd - bodyStart + 1);
                std::smatch ptrMatch;
                if (!std::regex_search(body, ptrMatch, ptrPattern))
                {
                    ++totalSkipped;
                    skippedWrappers.push_back(file.filename().string() + ": " + methodName);
                    continue;
                }

                const std::string calledPtr = ptrMatch[1].str();
                ++totalChecked;
                if (methodName != calledPtr)
                {
                    mismatches.push_back(file.filename().string() + ": " + methodName + " calls _nfx_" + calledPtr);
                }
            }
        }

        INFO("Total wrapper methods: " << totalWrappers);
        INFO("Total checked wrapper calls: " << totalChecked);
        INFO("Total skipped non-dynamic wrappers: " << totalSkipped);
        CHECK(totalWrappers > 0);
        CHECK(totalWrappers == totalChecked + totalSkipped);
        if (!mismatches.empty())
        {
            std::ostringstream os;
            os << "Wrapper call mismatches found:\n";
            for (const auto& m : mismatches)
            {
                os << " - " << m << "\n";
            }
            FAIL_CHECK(os.str());
        }

        if (totalSkipped > 0)
        {
            INFO("Example skipped wrapper: " << skippedWrappers.front());
        }
    }
}
