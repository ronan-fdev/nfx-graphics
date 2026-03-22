#==============================================================================
# nfx::graphics::gl - Sources
#==============================================================================

set(NFX_GRAPHICS_GL_SOURCES
    # Functions
    $<$<PLATFORM_ID:Linux>:src/gl/core/functions/loader/X11FunctionLoader.cpp>
    $<$<PLATFORM_ID:Windows>:src/gl/core/functions/loader/Win32FunctionLoader.cpp>
    src/gl/core/functions/Functions_1_0.cpp
    src/gl/core/functions/Functions_1_1.cpp
    src/gl/core/functions/Functions_1_2.cpp
    src/gl/core/functions/Functions_1_3.cpp
    src/gl/core/functions/Functions_1_4.cpp
    src/gl/core/functions/Functions_1_5.cpp
    src/gl/core/functions/Functions_2_0.cpp
    src/gl/core/functions/Functions_2_1.cpp
    src/gl/core/functions/Functions_3_0.cpp
    src/gl/core/functions/Functions_3_1.cpp
    src/gl/core/functions/Functions_3_2.cpp
    src/gl/core/functions/Functions_3_3.cpp
    src/gl/core/functions/Functions_4_0.cpp
    src/gl/core/functions/Functions_4_1.cpp
    src/gl/core/functions/Functions_4_2.cpp
    src/gl/core/functions/Functions_4_3.cpp
    src/gl/core/functions/Functions_4_4.cpp
    src/gl/core/functions/Functions_4_5.cpp
    src/gl/core/functions/Functions_4_6.cpp
    src/gl/core/Context.cpp
)
