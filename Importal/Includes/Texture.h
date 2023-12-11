#pragma once
#include "GlExt.h"

namespace Importal
{
    class Texture
    {
    public:
        Texture(const std::string& path,
                GLfloat MIN_FILTER = GL_LINEAR,
                GLfloat MAG_FILTER = GL_LINEAR,
                GLfloat WRAP_S = GL_CLAMP_TO_EDGE,
                GLfloat WRAP_T = GL_CLAMP_TO_EDGE);
        ~Texture();
    public:
        void Bind(GLuint slot = 0);
        void Unbind();

        inline GLint GetWidth() const;
        inline GLint GetHeight() const;
    private:
        GLuint _id;
        std::string _filepath;
        GLint _width, _height, _BPP;
    };
}
