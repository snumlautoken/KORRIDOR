#pragma once

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Input {
public:
    Input(GLFWwindow* window);
    void pollEvents();
    glm::mat4 getView();
    glm::vec3 getPos() {return pos;}
    glm::vec3 getUp() {return up;}
    void setPos(glm::vec3 newPos) {pos = newPos;}

    bool jump = false;
private:
    void processKb(double dT);
    void processM(double dT);

    GLFWwindow* window;
    glm::vec3 pos   = glm::vec3(0.0f, 1.5f,  0.0f);
    glm::vec3 dir   = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up    = glm::vec3(0.0f, 1.0f,  0.0f);

    double time;
    double prevX, prevY;
    float yaw, pitch = 0.0f;
};
