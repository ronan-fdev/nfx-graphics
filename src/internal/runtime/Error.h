#pragma once

#include <string_view>

namespace nfx::graphics::internal::runtime
{
    enum class ErrorLevel
    {
        Warn,
        Error
    };

    enum class ErrorKind
    {
        Programming,
        Recoverable,
        Invariant,
        External
    };

    void logError(std::string_view module, ErrorLevel level, ErrorKind kind, std::string_view message);
    void logError(std::string_view module, ErrorLevel level, std::string_view kind, std::string_view message);
} // namespace nfx::graphics::internal::runtime
