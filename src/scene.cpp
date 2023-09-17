#include "scene.hpp"

Scene::Scene(std::shared_ptr<Graphics> g, Player p)  : player(p) {
    gr_ptr = g;
}

void Scene::playerCollision() {
    for (auto l : entities) {
        for (auto e : l.second) {
            auto c = Entity::checkCollision(player,*e.get());
            if (c.collision) {
                player.move(-c.penVec);
            }
        }
    }
}

void Scene::render() {
    Prism::sp.use();
    Prism::sp.loadUniform("view", gr_ptr->input->getView());
    for (auto l : entities) {
        for (auto e : l.second) {
            e->render();
        }
    }

    gr_ptr->draw(prisms);
    gr_ptr->draw(*skybox);
    gr_ptr->render();
}
