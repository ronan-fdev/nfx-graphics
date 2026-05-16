#include "Error.h"

#include <cstdio>

namespace nfx::graphics::internal::runtime
{
    namespace
    {
        const char* toString(ErrorLevel level)
        {
            switch (level)
            {
                case ErrorLevel::Warn:
                    return "WARN";
                case ErrorLevel::Error:
                    return "ERROR";
            }
            return "ERROR";
        }

        const char* toString(ErrorKind kind)
        {
            switch (kind)
            {
                case ErrorKind::Programming:
                    return "PROGRAMMING";
                case ErrorKind::Recoverable:
                    return "RECOVERABLE";
                case ErrorKind::Invariant:
                    return "INVARIANT";
                case ErrorKind::External:
                    return "EXTERNAL";
            }
            return "EXTERNAL";
        }
    } // namespace

    void logError(std::string_view module, ErrorLevel level, std::string_view kind, std::string_view message)
    {
        std::fprintf(
            stderr,
            "[%.*s] %s(%.*s): %.*s\n",
            static_cast<int>(module.size()),
            module.data(),
            toString(level),
            static_cast<int>(kind.size()),
            kind.data(),
            static_cast<int>(message.size()),
            message.data());
    }

    void logError(std::string_view module, ErrorLevel level, ErrorKind kind, std::string_view message)
    {
        logError(module, level, toString(kind), message);
    }
} // namespace nfx::graphics::internal::runtime
