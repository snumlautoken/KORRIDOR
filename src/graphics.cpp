#include "graphics.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <filesystem>

Graphics::Graphics(int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(width, height, "KORRIDOR", nullptr, nullptr);
    glewExperimental = GL_TRUE;

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetFramebufferSizeCallback(window, 
        [](GLFWwindow* window, int width, int height) {glViewport(0, 0, width, height);}
    );

    glewInit();

    input = std::make_shared<Input>(window);
    glEnable(GL_MULTISAMPLE);  
    glEnable(GL_DEPTH_TEST);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.01f, 1000.0f);
    
    Shader sbprogram("shaders/skybox.vs", "shaders/skybox.fs");
    sr = std::make_unique<SkyboxRenderer>(sbprogram);
    sbprogram.use();
    sbprogram.loadUniform("projection", projection);
}

void Graphics::draw(std::vector<Prism> prisms) {
    for (auto prism : prisms) {
        prism.render();
    }
}
void Graphics::draw(Skybox skybox) {
    sr->shaderProgram.use();
    glm::mat4 view = input->getView();
    view = glm::mat4(glm::mat3(view));
    sr->shaderProgram.loadUniform("view", view);
    sr->render(skybox);
}


void Graphics::render() {
    glfwSwapBuffers(window);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    input->pollEvents();
}
