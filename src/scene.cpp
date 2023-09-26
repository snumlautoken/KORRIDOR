#include "scene.hpp"

Scene::Scene(std::shared_ptr<Graphics> g, Player p) : player(p) {
    gr_ptr = g;
}

void Scene::playerCollision() {
    glm::vec3 sum(0);
    for (auto e : entities) {
        auto c = Entity::checkCollision(player,*e.get());
        if (c.collision) {
            player.move(-c.penVec);
            if (c.penVec.y != 0) {
                double penVecYNorm = std::abs(glm::normalize(-c.penVec).y);
                player.velocity.y -= penVecYNorm*player.velocity.y;
            }
        }
    }
}

void Scene::render() {
    for (auto l : renderables) {
        l.second.begin()->get()->bindClass(gr_ptr->input->getView());
        for (auto e : l.second) {
            e->render();
        }
    }

    gr_ptr->draw(prisms);
    gr_ptr->draw(*skybox);
    gr_ptr->render();
}
