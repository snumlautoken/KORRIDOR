#include "scene.hpp"
#include <iostream>

void createPillar(Scene& scene, glm::vec3 pos, float height, Texture tex) {
    scene.prisms.push_back(Prism(pos,0,glm::vec3(0,1,0),glm::vec3(0.5, 0.1, 0.5), tex));
    scene.prisms.push_back(Prism(pos + glm::vec3(0,height/2,0),0,glm::vec3(0,1,0),glm::vec3(0.25, height, 0.25), tex));
    scene.prisms.push_back(Prism(pos + glm::vec3(0,height,0),0,glm::vec3(0,1,0),glm::vec3(0.5, 0.1, 0.5), tex));
}

int main() {
    std::shared_ptr<Graphics> graphics = std::make_shared<Graphics>(1000,1000);

    graphics->loadTex("grass.png");
    graphics->loadTex("tile.jpg");
    graphics->loadTex("cheese.png");
    

    Scene scene(graphics);

    Player p(0.4,1.5,graphics->input);

    scene.prisms.push_back(Prism(glm::vec3(0.0,-0.05,0.0),45,glm::vec3(0.0,1.0,0.0),glm::vec3(100.0, 0.1, 100.0), graphics->textures[0]));
    scene.prisms.push_back(Prism(glm::vec3(0,1.5,0),0,glm::vec3(1),glm::vec3(0.3), graphics->textures[2]));
    scene.prisms.push_back(Prism(glm::vec3(9.56,1.5,10),0,glm::vec3(1),glm::vec3(0.3), graphics->textures[2]));
    scene.prisms.push_back(Prism(glm::vec3(10,1.5,10.0),90,glm::vec3(1,1,0),glm::vec3(0.3,0.3,0.4), graphics->textures[2]));
    scene.prisms.push_back(Prism(glm::vec3(9.56,1.8,10),0,glm::vec3(1),glm::vec3(0.3), graphics->textures[2]));
    scene.prisms.push_back(Prism(glm::vec3(9.86,1.8,10.3),0,glm::vec3(1),glm::vec3(0.3), graphics->textures[2]));
    scene.prisms.push_back(Prism(glm::vec3(9.56,1.5,10),0,glm::vec3(1),glm::vec3(0.3), graphics->textures[2]));
    scene.prisms[1].scaleTex = false;
    scene.prisms.push_back(Prism(glm::vec3(-10.0,5,-10.0),0,glm::vec3(0.0,1.0,0.0),glm::vec3(10.0, 10, 1.0), graphics->textures[1]));
    createPillar(scene, glm::vec3(0),1,graphics->textures[1]);



    for (int i = 0; i < 20; i++) {
        createPillar(scene, glm::vec3(20-2*i,0,2),3,graphics->textures[1]);
        createPillar(scene, glm::vec3(20-2*i,0,-2),3, graphics->textures[1]);
    }


    scene.prisms.push_back(Prism(glm::vec3(1,3.2,0),0,glm::vec3(0,1,0),glm::vec3(40.0, 0.25, 6.0), graphics->textures[1]));

    scene.skybox = std::make_unique<Skybox>("resources/skybox");

    Prism& cheese = scene.prisms[1];

    while(!glfwWindowShouldClose(graphics->window)) {
        double time = glfwGetTime();
        /*cheese.setRot(20 * time);
        glm::vec3 newPos = cheese.getPos();
        newPos.y = 1.5+0.2*sin(time);
        cheese.setPos(newPos);*/
        p.update();
        auto c = Entity::checkCollision(p,scene.prisms[7]);
        if (c.collision) {
            p.move(-c.penVec);
        }
        c = Entity::checkCollision(p,scene.prisms[0]);
        if (c.collision) {
            p.move(c.penVec);
        }

        /*if (scene.prisms[2].checkCollision(scene.prisms[2+1]).collision) {
            std::cout << "2: " << time << std::endl;
        }

        if (scene.prisms[2].checkCollision(scene.prisms[3+1]).collision) {
            std::cout << "3: " << time << std::endl;
        }

        if (scene.prisms[2].checkCollision(scene.prisms[4+1]).collision) {
            std::cout << "4: " << time << std::endl;
        }

        if (scene.prisms[2].checkCollision(scene.prisms[5+1]).collision) {
            std::cout << "5: " << time << std::endl;
        }*/
        scene.render();
    }
    return 0;
}
