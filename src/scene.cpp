#include "scene.hpp"

Scene::Scene(std::shared_ptr<Graphics> g) {
    gr_ptr = g;
}

void Scene::render() {
    gr_ptr->draw(prisms);
    gr_ptr->draw(*skybox);
    gr_ptr->render();
}
