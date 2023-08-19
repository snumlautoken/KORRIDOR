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
    glm::mat4 model = p.model();
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(scale, p.scale);
    glm::mat3 invModel = glm::mat3(glm::transpose(glm::inverse(model)));
    shaderProgram.loadUniform("model", model);
    shaderProgram.loadUniform("scale", glm::mat3(scale));
    shaderProgram.loadUniform("invModel", invModel);
    glBindTexture(GL_TEXTURE_2D, p.tex);
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
}

glm::mat4 Prism::model() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(rot), axis);
    model = glm::scale(model, scale);

    return model;
}
