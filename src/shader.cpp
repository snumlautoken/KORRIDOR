#include <sstream>
#include <fstream>
#include <iostream>
#include "shader.hpp"

void Shader::loadUniform(std::string loc, glm::mat4 u) {
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, loc.c_str()), 1, GL_FALSE, &u[0][0]);
}

void Shader::loadUniform(std::string loc, glm::vec3 u) {
    glUniform3fv(glGetUniformLocation(shaderProgram, loc.c_str()), 1, &u[0]);
}

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    std::stringstream ss{ };
    std::string vertexShaderSource{ };
    std::string fragmentShaderSource{ };
    std::ifstream file{ vertexShaderPath };
    if (file.is_open()) {
        ss << file.rdbuf();
        vertexShaderSource = ss.str();
        file.close();
    }
    ss.str(std::string{ });

    file.open(fragmentShaderPath);
    if (file.is_open()) {
        ss << file.rdbuf();
        fragmentShaderSource = ss.str();
        file.close();
    }
    GLuint program = glCreateProgram();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* cVertexSource = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &cVertexSource, nullptr);
    glCompileShader(vertexShader);
    const char* cFragmentSource = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &cFragmentSource, nullptr);
    glCompileShader(fragmentShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    shaderProgram = program;
}

void Shader::use() {
    glUseProgram(shaderProgram);
}
