#pragma once
#include "shader.hpp"
#include "entity.hpp"
#include <memory>

class Renderer {
public:
    Renderer(Shader program) : shaderProgram(program) {};
    virtual void render(std::unique_ptr<Entity> e) {};

    Shader shaderProgram;
protected:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
};
