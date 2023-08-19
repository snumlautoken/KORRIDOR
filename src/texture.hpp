#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/gl.h>

class Texture {
public:
    Texture(std::string file);
    GLuint tex;
};
