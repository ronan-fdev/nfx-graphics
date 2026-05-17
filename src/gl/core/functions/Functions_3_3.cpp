#include "nfx/graphics/gl/core/functions/Functions_3_3.h"

#include "loader/FunctionLoader.h"
#include "loader/FunctionPointers.h"
#include "Errors.h"

namespace nfx::graphics::gl
{
    Functions_3_3::Functions_3_3()
        : Functions_3_2{}
    {}

    Functions_3_3::~Functions_3_3()
    {
        s_loaded = false;
    }

    GLvoid Functions_3_3::glBindFragDataLocationIndexed(
        GLuint program, GLuint colorNumber, GLuint index, const GLchar* name, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindFragDataLocationIndexed(program, colorNumber, index, name), caller);
    }

    GLvoid Functions_3_3::glBindSampler(GLuint unit, GLuint sampler, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glBindSampler(unit, sampler), caller);
    }

    GLvoid Functions_3_3::glColorP3ui(GLenum type, GLuint color, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glColorP3ui(type, color), caller);
    }

    GLvoid Functions_3_3::glColorP3uiv(GLenum type, const GLuint* color, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glColorP3uiv(type, color), caller);
    }

    GLvoid Functions_3_3::glColorP4ui(GLenum type, GLuint color, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glColorP4ui(type, color), caller);
    }

    GLvoid Functions_3_3::glColorP4uiv(GLenum type, const GLuint* color, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glColorP4uiv(type, color), caller);
    }

    GLvoid Functions_3_3::glDeleteSamplers(
        GLsizei count, const GLuint* samplers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glDeleteSamplers(count, samplers), caller);
    }

    GLvoid Functions_3_3::glGenSamplers(GLsizei count, GLuint* samplers, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGenSamplers(count, samplers), caller);
    }

    GLvoid Functions_3_3::glGetQueryObjecti64v(
        GLuint id, GLenum pname, GLint64* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetQueryObjecti64v(id, pname, params), caller);
    }

    GLvoid Functions_3_3::glGetQueryObjectui64v(
        GLuint id, GLenum pname, GLuint64* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetQueryObjectui64v(id, pname, params), caller);
    }

    GLvoid Functions_3_3::glGetSamplerParameterfv(
        GLuint sampler, GLenum pname, GLfloat* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetSamplerParameterfv(sampler, pname, params), caller);
    }

    GLvoid Functions_3_3::glGetSamplerParameteriv(
        GLuint sampler, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetSamplerParameteriv(sampler, pname, params), caller);
    }

    GLvoid Functions_3_3::glGetSamplerParameterIuiv(
        GLuint sampler, GLenum pname, GLuint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetSamplerParameterIuiv(sampler, pname, params), caller);
    }

    GLvoid Functions_3_3::glGetSamplerParameterIiv(
        GLuint sampler, GLenum pname, GLint* params, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glGetSamplerParameterIiv(sampler, pname, params), caller);
    }

    GLboolean Functions_3_3::glIsSampler(GLuint sampler, [[maybe_unused]] const char* caller) const
    {
        GLboolean ret{ false };

        NFX_GRAPHICS_GL_CHECK_ERROR(ret = _nfx_glIsSampler(sampler), caller);

        return ret;
    }

    GLvoid Functions_3_3::glMultiTexCoordP1ui(
        GLenum texture, GLenum type, GLuint coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoordP1ui(texture, type, coords), caller);
    }

    GLvoid Functions_3_3::glMultiTexCoordP1uiv(
        GLenum texture, GLenum type, const GLuint* coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoordP1uiv(texture, type, coords), caller);
    }

    GLvoid Functions_3_3::glMultiTexCoordP2ui(
        GLenum texture, GLenum type, GLuint coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoordP2ui(texture, type, coords), caller);
    }

    GLvoid Functions_3_3::glMultiTexCoordP2uiv(
        GLenum texture, GLenum type, const GLuint* coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoordP2uiv(texture, type, coords), caller);
    }

    GLvoid Functions_3_3::glMultiTexCoordP3ui(
        GLenum texture, GLenum type, GLuint coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoordP3ui(texture, type, coords), caller);
    }

    GLvoid Functions_3_3::glMultiTexCoordP3uiv(
        GLenum texture, GLenum type, const GLuint* coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoordP3uiv(texture, type, coords), caller);
    }

    GLvoid Functions_3_3::glMultiTexCoordP4ui(
        GLenum texture, GLenum type, GLuint coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoordP4ui(texture, type, coords), caller);
    }

    GLvoid Functions_3_3::glMultiTexCoordP4uiv(
        GLenum texture, GLenum type, const GLuint* coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glMultiTexCoordP4uiv(texture, type, coords), caller);
    }

    GLvoid Functions_3_3::glNormalP3ui(GLenum type, GLuint coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glNormalP3ui(type, coords), caller);
    }

    GLvoid Functions_3_3::glNormalP3uiv(GLenum type, const GLuint* coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glNormalP3uiv(type, coords), caller);
    }

    GLvoid Functions_3_3::glQueryCounter(GLuint id, GLenum target, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glQueryCounter(id, target), caller);
    }

    GLvoid Functions_3_3::glSamplerParameterf(
        GLuint sampler, GLenum pname, GLfloat param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSamplerParameterf(sampler, pname, param), caller);
    }

    GLvoid Functions_3_3::glSamplerParameterfv(
        GLuint sampler, GLenum pname, const GLfloat* param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSamplerParameterfv(sampler, pname, param), caller);
    }

    GLvoid Functions_3_3::glSamplerParameteri(
        GLuint sampler, GLenum pname, GLint param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSamplerParameteri(sampler, pname, param), caller);
    }

    GLvoid Functions_3_3::glSamplerParameterIiv(
        GLuint sampler, GLenum pname, const GLint* param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSamplerParameterIiv(sampler, pname, param), caller);
    }

    GLvoid Functions_3_3::glSamplerParameterIuiv(
        GLuint sampler, GLenum pname, const GLuint* param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSamplerParameterIuiv(sampler, pname, param), caller);
    }

    GLvoid Functions_3_3::glSamplerParameteriv(
        GLuint sampler, GLenum pname, const GLint* param, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSamplerParameteriv(sampler, pname, param), caller);
    }

    GLvoid Functions_3_3::glSecondaryColorP3ui(GLenum type, GLuint color, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColorP3ui(type, color), caller);
    }

    GLvoid Functions_3_3::glSecondaryColorP3uiv(
        GLenum type, const GLuint* color, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glSecondaryColorP3uiv(type, color), caller);
    }

    GLvoid Functions_3_3::glTexCoordP1ui(GLenum type, GLuint coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTexCoordP1ui(type, coords), caller);
    }

    GLvoid Functions_3_3::glTexCoordP1uiv(GLenum type, const GLuint* coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTexCoordP1uiv(type, coords), caller);
    }

    GLvoid Functions_3_3::glTexCoordP2ui(GLenum type, GLuint coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTexCoordP2ui(type, coords), caller);
    }

    GLvoid Functions_3_3::glTexCoordP2uiv(GLenum type, const GLuint* coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTexCoordP2uiv(type, coords), caller);
    }

    GLvoid Functions_3_3::glTexCoordP3ui(GLenum type, GLuint coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTexCoordP3ui(type, coords), caller);
    }

    GLvoid Functions_3_3::glTexCoordP3uiv(GLenum type, const GLuint* coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTexCoordP3uiv(type, coords), caller);
    }

    GLvoid Functions_3_3::glTexCoordP4ui(GLenum type, GLuint coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTexCoordP4ui(type, coords), caller);
    }

    GLvoid Functions_3_3::glTexCoordP4uiv(GLenum type, const GLuint* coords, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glTexCoordP4uiv(type, coords), caller);
    }

    GLvoid Functions_3_3::glVertexAttribDivisor(GLuint index, GLuint divisor, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribDivisor(index, divisor), caller);
    }

    GLvoid Functions_3_3::glVertexAttribP1ui(
        GLuint index, GLenum type, GLboolean normalized, GLuint value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribP1ui(index, type, normalized, value), caller);
    }

    GLvoid Functions_3_3::glVertexAttribP1uiv(
        GLuint index, GLenum type, GLboolean normalized, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribP1uiv(index, type, normalized, value), caller);
    }

    GLvoid Functions_3_3::glVertexAttribP2ui(
        GLuint index, GLenum type, GLboolean normalized, GLuint value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribP2ui(index, type, normalized, value), caller);
    }

    GLvoid Functions_3_3::glVertexAttribP2uiv(
        GLuint index, GLenum type, GLboolean normalized, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribP2uiv(index, type, normalized, value), caller);
    }

    GLvoid Functions_3_3::glVertexAttribP3ui(
        GLuint index, GLenum type, GLboolean normalized, GLuint value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribP3ui(index, type, normalized, value), caller);
    }

    GLvoid Functions_3_3::glVertexAttribP3uiv(
        GLuint index, GLenum type, GLboolean normalized, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribP3uiv(index, type, normalized, value), caller);
    }

    GLvoid Functions_3_3::glVertexAttribP4ui(
        GLuint index, GLenum type, GLboolean normalized, GLuint value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribP4ui(index, type, normalized, value), caller);
    }

    GLvoid Functions_3_3::glVertexAttribP4uiv(
        GLuint index, GLenum type, GLboolean normalized, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexAttribP4uiv(index, type, normalized, value), caller);
    }

    GLvoid Functions_3_3::glVertexP2ui(GLenum type, GLuint value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexP2ui(type, value), caller);
    }

    GLvoid Functions_3_3::glVertexP2uiv(GLenum type, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexP2uiv(type, value), caller);
    }

    GLvoid Functions_3_3::glVertexP3ui(GLenum type, GLuint value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexP3ui(type, value), caller);
    }

    GLvoid Functions_3_3::glVertexP3uiv(GLenum type, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexP3uiv(type, value), caller);
    }

    GLvoid Functions_3_3::glVertexP4ui(GLenum type, GLuint value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexP4ui(type, value), caller);
    }

    GLvoid Functions_3_3::glVertexP4uiv(GLenum type, const GLuint* value, [[maybe_unused]] const char* caller) const
    {
        NFX_GRAPHICS_GL_CHECK_ERROR(_nfx_glVertexP4uiv(type, value), caller);
    }

    bool Functions_3_3::initialize()
    {
        Functions_3_2::initialize();

        if (s_loaded)
        {
            return s_loaded;
        }

        FunctionLoader loader;

        _nfx_glBindFragDataLocationIndexed = reinterpret_cast<GLvoid (*)(GLuint, GLuint, GLuint, const GLchar*)>(
            loader.loadFunctionPtr("glBindFragDataLocationIndexed"));
        _nfx_glBindSampler = reinterpret_cast<GLvoid (*)(GLuint, GLuint)>(loader.loadFunctionPtr("glBindSampler"));
        _nfx_glColorP3ui = reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glColorP3ui"));
        _nfx_glColorP3uiv = reinterpret_cast<GLvoid (*)(GLenum, const GLuint*)>(loader.loadFunctionPtr("glColorP3uiv"));
        _nfx_glColorP4ui = reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glColorP4ui"));
        _nfx_glColorP4uiv = reinterpret_cast<GLvoid (*)(GLenum, const GLuint*)>(loader.loadFunctionPtr("glColorP4uiv"));
        _nfx_glDeleteSamplers =
            reinterpret_cast<GLvoid (*)(GLsizei, const GLuint*)>(loader.loadFunctionPtr("glDeleteSamplers"));
        _nfx_glGenSamplers = reinterpret_cast<GLvoid (*)(GLsizei, GLuint*)>(loader.loadFunctionPtr("glGenSamplers"));
        _nfx_glGetQueryObjecti64v =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint64*)>(loader.loadFunctionPtr("glGetQueryObjecti64v"));
        _nfx_glGetQueryObjectui64v =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint64*)>(loader.loadFunctionPtr("glGetQueryObjectui64v"));
        _nfx_glGetSamplerParameterfv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLfloat*)>(loader.loadFunctionPtr("glGetSamplerParameterfv"));
        _nfx_glGetSamplerParameterIiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint*)>(loader.loadFunctionPtr("glGetSamplerParameterIiv"));
        _nfx_glGetSamplerParameterIuiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLuint*)>(loader.loadFunctionPtr("glGetSamplerParameterIuiv"));
        _nfx_glGetSamplerParameteriv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint*)>(loader.loadFunctionPtr("glGetSamplerParameteriv"));
        _nfx_glIsSampler = reinterpret_cast<GLboolean (*)(GLuint)>(loader.loadFunctionPtr("glIsSampler"));
        _nfx_glMultiTexCoordP1ui =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLuint)>(loader.loadFunctionPtr("glMultiTexCoordP1ui"));
        _nfx_glMultiTexCoordP1uiv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, const GLuint*)>(loader.loadFunctionPtr("glMultiTexCoordP1uiv"));
        _nfx_glMultiTexCoordP2ui =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLuint)>(loader.loadFunctionPtr("glMultiTexCoordP2ui"));
        _nfx_glMultiTexCoordP2uiv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, const GLuint*)>(loader.loadFunctionPtr("glMultiTexCoordP2uiv"));
        _nfx_glMultiTexCoordP3ui =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLuint)>(loader.loadFunctionPtr("glMultiTexCoordP3ui"));
        _nfx_glMultiTexCoordP3uiv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, const GLuint*)>(loader.loadFunctionPtr("glMultiTexCoordP3uiv"));
        _nfx_glMultiTexCoordP4ui =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, GLuint)>(loader.loadFunctionPtr("glMultiTexCoordP4ui"));
        _nfx_glMultiTexCoordP4uiv =
            reinterpret_cast<GLvoid (*)(GLenum, GLenum, const GLuint*)>(loader.loadFunctionPtr("glMultiTexCoordP4uiv"));
        _nfx_glNormalP3ui = reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glNormalP3ui"));
        _nfx_glNormalP3uiv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLuint*)>(loader.loadFunctionPtr("glNormalP3uiv"));
        _nfx_glQueryCounter = reinterpret_cast<GLvoid (*)(GLuint, GLenum)>(loader.loadFunctionPtr("glQueryCounter"));
        _nfx_glSamplerParameterf =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLfloat)>(loader.loadFunctionPtr("glSamplerParameterf"));
        _nfx_glSamplerParameterfv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, const GLfloat*)>(
            loader.loadFunctionPtr("glSamplerParameterfv"));
        _nfx_glSamplerParameteri =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLint)>(loader.loadFunctionPtr("glSamplerParameteri"));
        _nfx_glSamplerParameterIiv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, const GLint*)>(loader.loadFunctionPtr("glSamplerParameterIiv"));
        _nfx_glSamplerParameterIuiv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, const GLuint*)>(
            loader.loadFunctionPtr("glSamplerParameterIuiv"));
        _nfx_glSamplerParameteriv =
            reinterpret_cast<GLvoid (*)(GLuint, GLenum, const GLint*)>(loader.loadFunctionPtr("glSamplerParameteriv"));
        _nfx_glSecondaryColorP3ui =
            reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glSecondaryColorP3ui"));
        _nfx_glSecondaryColorP3uiv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLuint*)>(loader.loadFunctionPtr("glSecondaryColorP3uiv"));
        _nfx_glTexCoordP1ui = reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glTexCoordP1ui"));
        _nfx_glTexCoordP1uiv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLuint*)>(loader.loadFunctionPtr("glTexCoordP1uiv"));
        _nfx_glTexCoordP2ui = reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glTexCoordP2ui"));
        _nfx_glTexCoordP2uiv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLuint*)>(loader.loadFunctionPtr("glTexCoordP2uiv"));
        _nfx_glTexCoordP3ui = reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glTexCoordP3ui"));
        _nfx_glTexCoordP3uiv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLuint*)>(loader.loadFunctionPtr("glTexCoordP3uiv"));
        _nfx_glTexCoordP4ui = reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glTexCoordP4ui"));
        _nfx_glTexCoordP4uiv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLuint*)>(loader.loadFunctionPtr("glTexCoordP4uiv"));
        _nfx_glVertexAttribDivisor =
            reinterpret_cast<GLvoid (*)(GLuint, GLuint)>(loader.loadFunctionPtr("glVertexAttribDivisor"));
        _nfx_glVertexAttribP1ui = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLboolean, GLuint)>(
            loader.loadFunctionPtr("glVertexAttribP1ui"));
        _nfx_glVertexAttribP1uiv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLboolean, const GLuint*)>(
            loader.loadFunctionPtr("glVertexAttribP1uiv"));
        _nfx_glVertexAttribP2ui = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLboolean, GLuint)>(
            loader.loadFunctionPtr("glVertexAttribP2ui"));
        _nfx_glVertexAttribP2uiv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLboolean, const GLuint*)>(
            loader.loadFunctionPtr("glVertexAttribP2uiv"));
        _nfx_glVertexAttribP3ui = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLboolean, GLuint)>(
            loader.loadFunctionPtr("glVertexAttribP3ui"));
        _nfx_glVertexAttribP3uiv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLboolean, const GLuint*)>(
            loader.loadFunctionPtr("glVertexAttribP3uiv"));
        _nfx_glVertexAttribP4ui = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLboolean, GLuint)>(
            loader.loadFunctionPtr("glVertexAttribP4ui"));
        _nfx_glVertexAttribP4uiv = reinterpret_cast<GLvoid (*)(GLuint, GLenum, GLboolean, const GLuint*)>(
            loader.loadFunctionPtr("glVertexAttribP4uiv"));
        _nfx_glVertexP2ui = reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glVertexP2ui"));
        _nfx_glVertexP2uiv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLuint*)>(loader.loadFunctionPtr("glVertexP2uiv"));
        _nfx_glVertexP3ui = reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glVertexP3ui"));
        _nfx_glVertexP3uiv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLuint*)>(loader.loadFunctionPtr("glVertexP3uiv"));
        _nfx_glVertexP4ui = reinterpret_cast<GLvoid (*)(GLenum, GLuint)>(loader.loadFunctionPtr("glVertexP4ui"));
        _nfx_glVertexP4uiv =
            reinterpret_cast<GLvoid (*)(GLenum, const GLuint*)>(loader.loadFunctionPtr("glVertexP4uiv"));

        return s_loaded = true;
    }

    void Functions_3_3::teardown()
    {
        nullifyPointers();

        s_loaded = false;

        Functions_3_2::teardown();
    }

    void Functions_3_3::nullifyPointers()
    {
        _nfx_glBindFragDataLocationIndexed = nullptr;
        _nfx_glBindSampler = nullptr;
        _nfx_glColorP3ui = nullptr;
        _nfx_glColorP3uiv = nullptr;
        _nfx_glColorP4ui = nullptr;
        _nfx_glColorP4uiv = nullptr;
        _nfx_glDeleteSamplers = nullptr;
        _nfx_glGenSamplers = nullptr;
        _nfx_glGetQueryObjecti64v = nullptr;
        _nfx_glGetQueryObjectui64v = nullptr;
        _nfx_glGetSamplerParameterfv = nullptr;
        _nfx_glGetSamplerParameterIiv = nullptr;
        _nfx_glGetSamplerParameterIuiv = nullptr;
        _nfx_glGetSamplerParameteriv = nullptr;
        _nfx_glIsSampler = nullptr;
        _nfx_glMultiTexCoordP1ui = nullptr;
        _nfx_glMultiTexCoordP1uiv = nullptr;
        _nfx_glMultiTexCoordP2ui = nullptr;
        _nfx_glMultiTexCoordP2uiv = nullptr;
        _nfx_glMultiTexCoordP3ui = nullptr;
        _nfx_glMultiTexCoordP3uiv = nullptr;
        _nfx_glMultiTexCoordP4ui = nullptr;
        _nfx_glMultiTexCoordP4uiv = nullptr;
        _nfx_glNormalP3ui = nullptr;
        _nfx_glNormalP3uiv = nullptr;
        _nfx_glQueryCounter = nullptr;
        _nfx_glSamplerParameterf = nullptr;
        _nfx_glSamplerParameterfv = nullptr;
        _nfx_glSamplerParameteri = nullptr;
        _nfx_glSamplerParameterIiv = nullptr;
        _nfx_glSamplerParameterIuiv = nullptr;
        _nfx_glSamplerParameteriv = nullptr;
        _nfx_glSecondaryColorP3ui = nullptr;
        _nfx_glSecondaryColorP3uiv = nullptr;
        _nfx_glTexCoordP1ui = nullptr;
        _nfx_glTexCoordP1uiv = nullptr;
        _nfx_glTexCoordP2ui = nullptr;
        _nfx_glTexCoordP2uiv = nullptr;
        _nfx_glTexCoordP3ui = nullptr;
        _nfx_glTexCoordP3uiv = nullptr;
        _nfx_glTexCoordP4ui = nullptr;
        _nfx_glTexCoordP4uiv = nullptr;
        _nfx_glVertexAttribDivisor = nullptr;
        _nfx_glVertexAttribP1ui = nullptr;
        _nfx_glVertexAttribP1uiv = nullptr;
        _nfx_glVertexAttribP2ui = nullptr;
        _nfx_glVertexAttribP2uiv = nullptr;
        _nfx_glVertexAttribP3ui = nullptr;
        _nfx_glVertexAttribP3uiv = nullptr;
        _nfx_glVertexAttribP4ui = nullptr;
        _nfx_glVertexAttribP4uiv = nullptr;
        _nfx_glVertexP2ui = nullptr;
        _nfx_glVertexP2uiv = nullptr;
        _nfx_glVertexP3ui = nullptr;
        _nfx_glVertexP3uiv = nullptr;
        _nfx_glVertexP4ui = nullptr;
        _nfx_glVertexP4uiv = nullptr;
    }
} // namespace nfx::graphics::gl
