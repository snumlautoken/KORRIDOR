#pragma once
#include <GL/glew.h>
#include <GL/gl.h>

class Texture {
public:
    Texture(const char* file);
    GLuint tex;
};
