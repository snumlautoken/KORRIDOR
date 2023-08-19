#include "scene.hpp"

void createPillar(Scene& scene, glm::vec3 pos, Texture tex) {
    scene.prisms.push_back(Prism(pos,0,glm::vec3(0,1,0),glm::vec3(0.5, 0.1, 0.5), tex));
    scene.prisms.push_back(Prism(pos + glm::vec3(0,1.5,0),0,glm::vec3(0,1,0),glm::vec3(0.25, 3, 0.25), tex));
    scene.prisms.push_back(Prism(pos + glm::vec3(0,3,0),0,glm::vec3(0,1,0),glm::vec3(0.5, 0.1, 0.5), tex));
}

int main() {

    std::shared_ptr<Graphics> graphics = std::make_shared<Graphics>(1000,1000);

    graphics->loadTex("grass.png");
    graphics->loadTex("tile.jpg");
    graphics->loadTex("cheese.png");
    

    Scene scene(graphics);

    scene.prisms.push_back(Prism(glm::vec3(0.0,-0.05,0.0),45,glm::vec3(0.0,1.0,0.0),glm::vec3(100.0, 0.1, 100.0), graphics->textures[0]));
    scene.prisms.push_back(Prism(glm::vec3(0.0,1,0.0),90,glm::vec3(1),glm::vec3(1.0, 1.0, 1.0), graphics->textures[2]));

    for (int i = 0; i < 20; i++) {
        createPillar(scene, glm::vec3(20-2*i,0,2), graphics->textures[1]);
        createPillar(scene, glm::vec3(20-2*i,0,-2), graphics->textures[1]);
    }

    scene.prisms.push_back(Prism(glm::vec3(1,3.2,0),0,glm::vec3(0,1,0),glm::vec3(40.0, 0.25, 6.0), graphics->textures[1]));

    scene.skybox = std::make_unique<Skybox>("resources/skybox");

    while(!glfwWindowShouldClose(graphics->window)) {
        scene.prisms[1].rot = glfwGetTime() * 40;
        scene.render();
    }
    return 0;
}
