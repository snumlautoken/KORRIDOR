#pragma once
#include <GL/glew.h>
#include <GL/gl.h>
#include "shader.hpp"
#include "texture.hpp"

class Renderable {
public:
    Renderable(Texture t) : tex(t) {}
    virtual void render() = 0;
    virtual Shader getProgram() = 0;
    virtual void bindClass(const glm::mat4& view) = 0;
protected:
    Texture tex;
};
