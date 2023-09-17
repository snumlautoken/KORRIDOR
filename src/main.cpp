#include "scene.hpp"
#include <iostream>

void createPillar(Scene& scene, glm::vec3 pos, float height, Texture tex) {
    scene.addEntity<Prism>(Prism(pos,0,glm::vec3(0,1,0),glm::vec3(0.5, 0.1, 0.5), tex));
    scene.addEntity<Prism>(Prism(pos + glm::vec3(0,height/2,0),0,glm::vec3(0,1,0),glm::vec3(0.25, height, 0.25), tex));
    scene.addEntity<Prism>(Prism(pos + glm::vec3(0,height,0),0,glm::vec3(0,1,0),glm::vec3(0.5, 0.1, 0.5), tex));
}

void createStairs(Scene& scene, glm::vec3 pos, int steps, Texture tex) {
    for (int i = 0; i < steps; i++) {
        scene.addEntity<Prism>(Prism(pos+glm::vec3(0,i/15.0,i/7.5),0,glm::vec3(0,1,0),glm::vec3(1, 1.0/15.0, 0.5), tex));
    }
}

int main() {
    std::shared_ptr<Graphics> graphics = std::make_shared<Graphics>(1000,1000);

    graphics->loadTex("grass.png");
    graphics->loadTex("tile.jpg");
    graphics->loadTex("cheese.png");
    

    Scene scene(graphics, Player(0.2,1.5,graphics->input));

    Prism::createRenderer(Shader("shaders/prism.vs", "shaders/prism.fs"));

    scene.addEntity<Prism>(Prism(glm::vec3(0.0,-0.05,0.0),45,glm::vec3(0.0,1.0,0.0),glm::vec3(100.0, 0.1, 100.0), graphics->textures[0]));
    scene.addEntity<Prism>(Prism(glm::vec3(1,1,0),0,glm::vec3(1),glm::vec3(0.3), graphics->textures[2]));
    scene.addEntity<Prism>(Prism(glm::vec3(9.56,1.5,10),0,glm::vec3(1),glm::vec3(0.3), graphics->textures[2]));
    scene.addEntity<Prism>(Prism(glm::vec3(10,1.5,10.0),90,glm::vec3(1,1,0),glm::vec3(0.3,0.3,0.4), graphics->textures[2]));
    scene.addEntity<Prism>(Prism(glm::vec3(9.56,1.8,10),0,glm::vec3(1),glm::vec3(0.3), graphics->textures[2]));
    scene.addEntity<Prism>(Prism(glm::vec3(9.86,1.8,10.3),0,glm::vec3(1),glm::vec3(0.3), graphics->textures[2]));
    scene.addEntity<Prism>(Prism(glm::vec3(9.56,1.5,10),0,glm::vec3(1),glm::vec3(0.3), graphics->textures[2]));
    scene.addEntity<Prism>(Prism(glm::vec3(-10.0,5,-12.0),0,glm::vec3(0.0,1.0,0.0),glm::vec3(10.0, 10, 1.0), graphics->textures[1]));
    scene.addEntity<Prism>(Prism(glm::vec3(1,3.2,0),0,glm::vec3(0,1,0),glm::vec3(40.0, 0.25, 6.0), graphics->textures[1]));
    scene.addEntity<Prism>(Prism(glm::vec3(10.0,1,10.0),70,glm::vec3(1,0,0),glm::vec3(10.0, 10, 1.0), graphics->textures[1]));
    
    createPillar(scene, glm::vec3(0),1,graphics->textures[1]);
    createStairs(scene, glm::vec3(-18,-.3,-10),60,graphics->textures[1]);


    for (int i = 0; i < 20; i++) {
        createPillar(scene, glm::vec3(20-2*i,0,2),3,graphics->textures[1]);
        createPillar(scene, glm::vec3(20-2*i,0,-2),3, graphics->textures[1]);
    }

    scene.skybox = std::make_unique<Skybox>("resources/skybox");

    double lastTime = glfwGetTime();
    while(!glfwWindowShouldClose(graphics->window)) {
        double time = glfwGetTime();
        double deltaTime = time - lastTime;
        glm::vec3 gravity(0,-9.82,0);

        scene.player.update();
        scene.player.move(gravity*glm::vec3(deltaTime));

        scene.playerCollision();
        scene.render();
        lastTime = time;
    }
    return 0;
}
