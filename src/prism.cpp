#include "prism.hpp"
#include <iostream>

const float Prism::vertices[] = {
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
};

const float Prism::normals[] = {
    0,0,-1,
    0,0,-1,
    0,0,-1,
    0,0,-1,
    0,0,-1,
    0,0,-1,

    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,

    -1,0,0,
    -1,0,0,
    -1,0,0,
    -1,0,0,
    -1,0,0,
    -1,0,0,

    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,

    0,-1,0,
    0,-1,0,
    0,-1,0,
    0,-1,0,
    0,-1,0,
    0,-1,0,

    0,1,0,
    0,1,0,
    0,1,0,
    0,1,0,
    0,1,0,
    0,1,0
};

Shader Prism::program;
GLuint Prism::vao;
GLuint Prism::vbo;

void Prism::render() {
    glm::mat4 model = getModel();
    glm::mat4 scale = scaleTex ? glm::scale(glm::mat4(1.0f), getScale()) : glm::mat4(1.0f);
    glm::mat3 invModel = glm::mat3(glm::transpose(glm::inverse(model)));
    program.loadUniform("model", model);
    program.loadUniform("scale", glm::mat3(scale));
    program.loadUniform("invModel", invModel);
    tex.bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

Prism::Prism(glm::vec3 p, float r, glm::vec3 a, glm::vec3 d, Texture texture) : Renderable(texture) {
    pos = p;
    rot = r;
    axis = a;
    scale = d;

    recalcModel();
}

glm::mat4 Prism::getModel() {
    return model;
}

void Prism::recalcModel() {
    model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(rot), axis);
    model = glm::scale(model, scale);

    recalcVertices();
}

static const std::pair<glm::mat4,glm::mat4> defaultVert(   
    glm::mat4(
    glm::vec4(0.5,0.5,0.5,1),
    glm::vec4(0.5,0.5,-0.5,1),
    glm::vec4(0.5,-0.5,0.5,1),
    glm::vec4(-0.5,0.5,0.5,1)),
    glm::mat4(
    glm::vec4(-0.5,-0.5,-0.5,1),
    glm::vec4(-0.5,-0.5,0.5,1),
    glm::vec4(-0.5,0.5,-0.5,1),
    glm::vec4(0.5,-0.5,-0.5,1)));

void Prism::recalcVertices() {
    vert.first = model*defaultVert.first;
    vert.second = model*defaultVert.second;
}

glm::vec3 Prism::support(glm::vec3 dir) {
    float maxDot = -INFINITY;
    glm::vec3 maxCoord;
    dir = glm::normalize(dir);
    for (int i = 0; i < 4; i++) {
        glm::vec3 col = glm::vec3(vert.first[i]);
        float currDot = glm::dot(col-pos, dir);
        if (maxDot < currDot) {
            maxDot = currDot;
            maxCoord = col;
        }
    }
    for (int i = 0; i < 4; i++) {
        glm::vec3 col = glm::vec3(vert.second[i]);
        float currDot = glm::dot(col-pos, dir);
        if (maxDot < currDot) {
            maxDot = currDot;
            maxCoord = col;
        }
    }
    return maxCoord;
}
