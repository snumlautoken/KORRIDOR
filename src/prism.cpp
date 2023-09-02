#include "prism.hpp"
#include <iostream>

const float vertices[3*36] = {
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

const float normals[3*36] = {
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

PrismRenderer::PrismRenderer(Shader program) : shaderProgram(program) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(normals), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(normals), normals);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)(sizeof(vertices)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    program.use();
    shaderProgram.loadUniform("tex", 0);
}

void PrismRenderer::render(Prism p) {
    glm::mat4 model = p.getModel();
    glm::mat4 scale = p.scaleTex ? glm::scale(glm::mat4(1.0f), p.getScale()) : glm::mat4(1.0f);
    glm::mat3 invModel = glm::mat3(glm::transpose(glm::inverse(model)));
    shaderProgram.loadUniform("model", model);
    shaderProgram.loadUniform("scale", glm::mat3(scale));
    shaderProgram.loadUniform("invModel", invModel);
    glBindTexture(GL_TEXTURE_2D, p.getTex());
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

Prism::Prism(glm::vec3 p, float r, glm::vec3 a, glm::vec3 d, Texture texture) {
    pos = p;
    rot = r;
    axis = a;
    scale = d;
    tex = texture.tex;

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
