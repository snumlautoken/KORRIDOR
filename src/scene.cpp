#include "scene.hpp"

Scene::Scene(std::shared_ptr<Graphics> g, Player p)  : player(p) {
    gr_ptr = g;
}

void Scene::playerCollision() {
    for (auto e : entities) {
        auto c = Entity::checkCollision(player,*e.get());
        if (c.collision) {
            player.move(-c.penVec);
        }
    }
}

void Scene::render() {
    for (auto l : renderables) {
        auto sp = l.second.begin()->get()->getProgram();
        sp.use();
        sp.loadUniform("view", gr_ptr->input->getView());
        for (auto e : l.second) {
            e->render();
        }
    }

    gr_ptr->draw(prisms);
    gr_ptr->draw(*skybox);
    gr_ptr->render();
}
