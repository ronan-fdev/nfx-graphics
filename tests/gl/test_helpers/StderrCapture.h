#pragma once

#include <doctest/doctest.h>

#include <cstdio>
#include <string>

#ifdef __linux__
    #include <unistd.h>
#elif defined(_WIN32)
    #include <io.h>
#endif

namespace nfx::tests
{
#ifdef __linux__
    constexpr auto kDup = dup;
    constexpr auto kDup2 = dup2;
    constexpr auto kClose = close;
    constexpr auto kFileno = ::fileno;
#elif defined(_WIN32)
    constexpr auto kDup = _dup;
    constexpr auto kDup2 = _dup2;
    constexpr auto kClose = _close;
    constexpr auto kFileno = _fileno;
#endif

    struct StderrCapture
    {
        std::FILE* file = nullptr;
        int savedFd = -1;
        int captureFd = -1;

        StderrCapture()
        {
#ifdef __linux__
            file = std::tmpfile();
#elif defined(_WIN32)
            tmpfile_s(&file);
#endif
            REQUIRE(file != nullptr);

            ::fflush(stderr);
            savedFd = kDup(kFileno(stderr));
            REQUIRE(savedFd >= 0);

            captureFd = kFileno(file);
            REQUIRE(kDup2(captureFd, kFileno(stderr)) >= 0);
        }

        ~StderrCapture()
        {
            ::fflush(stderr);
            if (savedFd >= 0)
            {
                kDup2(savedFd, kFileno(stderr));
                kClose(savedFd);
            }
            if (file)
            {
                ::fclose(file);
            }
        }

        [[nodiscard]] std::string str()
        {
            ::fflush(stderr);
            ::fflush(file);
            REQUIRE(::fseek(file, 0, SEEK_END) == 0);
            const long length = ::ftell(file);
            REQUIRE(length >= 0);
            REQUIRE(::fseek(file, 0, SEEK_SET) == 0);

            std::string out(static_cast<std::size_t>(length), '\0');
            if (length > 0)
            {
                const std::size_t read = ::fread(out.data(), 1, static_cast<std::size_t>(length), file);
                REQUIRE(read == static_cast<std::size_t>(length));
            }
            return out;
        }
    };
} // namespace nfx::tests
