#include <doctest/doctest.h>

#include "internal/runtime/Error.h"
#include "../test_helpers/StderrCapture.h"

using namespace nfx::graphics::internal::runtime;
using nfx::tests::StderrCapture;

TEST_SUITE("RuntimeError")
{
    TEST_CASE("logError formats enum kind")
    {
        StderrCapture capture;
        logError("Module", ErrorLevel::Warn, ErrorKind::Recoverable, "something happened");
        CHECK(capture.str() == "[Module] WARN(RECOVERABLE): something happened\n");
    }

    TEST_CASE("logError formats custom string kind")
    {
        StderrCapture capture;
        logError("GLDebug", ErrorLevel::Warn, "GLDebug", "called by foo");
        CHECK(capture.str() == "[GLDebug] WARN(GLDebug): called by foo\n");
    }

    TEST_CASE("logError formats error level")
    {
        StderrCapture capture;
        logError("Renderer", ErrorLevel::Error, ErrorKind::External, "resource missing");
        CHECK(capture.str() == "[Renderer] ERROR(EXTERNAL): resource missing\n");
    }
}
