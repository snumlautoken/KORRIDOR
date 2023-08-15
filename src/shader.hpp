#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void use();
    void loadUniform(std::string loc, glm::mat4 u);
    void loadUniform(std::string loc, glm::vec3 u);
private:
    GLuint shaderProgram;
};
