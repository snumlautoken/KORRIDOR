#pragma once
#include <GL/glew.h>
#include <GL/gl.h>
#include "shader.hpp"

class Renderable {
public:
    virtual void render() = 0;
    virtual Shader getProgram() = 0;
};
