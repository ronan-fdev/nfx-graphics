#pragma once

#if defined(__linux__)
    #include <GL/gl.h>
    #include <GL/glext.h>
#elif defined(_WIN32)
    #include <windows.h>
    #include <GL/gl.h>
    #include <GL/glext.h>
#endif
