#include "graphics.hpp"
#include "prism.hpp"
#include "skybox.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <filesystem>

void printError() {
    std::cout << glGetError() << std::endl;
}

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

    input = std::make_unique<Input>(window);
    glEnable(GL_MULTISAMPLE);  
    glEnable(GL_DEPTH_TEST);

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 1000.0f);

    Shader program("shaders/object.vs", "shaders/object.fs");
    renderers.push_back(std::make_unique<PrismRenderer>(program));

    program.use();
    program.loadUniform("projection", projection);
    
    Shader sbprogram("shaders/skybox.vs", "shaders/skybox.fs");
    renderers.push_back(std::make_unique<SkyboxRenderer>(sbprogram));
    sbprogram.use();
    sbprogram.loadUniform("projection", projection);
}

void Graphics::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    input->pollEvents();
    glm::mat4 view;
    view = input->getView();

    renderers[0]->shaderProgram.use();
    renderers[0]->shaderProgram.loadUniform("view", view);
    renderers[0]->render(std::make_unique<Prism>(glm::vec3(0.0,-0.5,0.0),45,glm::vec3(0.0,1.0,0.0),glm::vec3(10.0, 1.0, 10.0)));
    renderers[0]->render(std::make_unique<Prism>(glm::vec3(0.0,1,0.0),45,glm::vec3(1.0,1.0,0.0),glm::vec3(1.0, 1.0, 1.0)));

    view = glm::mat4(glm::mat3(view));

    renderers[1]->shaderProgram.use();
    renderers[1]->shaderProgram.loadUniform("view", view);
    renderers[1]->render(nullptr);

    glfwSwapBuffers(window);
}
