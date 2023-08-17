#include "graphics.hpp"

int main() {

    Graphics graphics(1000,1000);

    std::vector<Prism> pv;

    pv.push_back(Prism(glm::vec3(0.0,-0.05,0.0),45,glm::vec3(0.0,1.0,0.0),glm::vec3(10.0, 0.1, 10.0), graphics.textures[0]));
    pv.push_back(Prism(glm::vec3(0.0,1,0.0),90,glm::vec3(1.0,1.0,0.0),glm::vec3(1.0, 1.0, 1.0), graphics.textures[1]));
    pv.push_back(Prism(glm::vec3(2.0,0.0,1.0),0,glm::vec3(1.0,1.0,0.0),glm::vec3(0.5, 0.1, 0.5), graphics.textures[1]));
    pv.push_back(Prism(glm::vec3(2.0,1.5,1.0),0,glm::vec3(1.0,1.0,0.0),glm::vec3(0.25, 3, 0.25), graphics.textures[1]));
    pv.push_back(Prism(glm::vec3(2.0,3.0,1.0),0,glm::vec3(1.0,1.0,0.0),glm::vec3(0.5, 0.1, 0.5), graphics.textures[1]));

    Skybox sb("resources/skybox");

    while(!glfwWindowShouldClose(graphics.window)) {
        graphics.draw(pv);
        graphics.draw(sb);
        graphics.render();
    }
    return 0;
}
