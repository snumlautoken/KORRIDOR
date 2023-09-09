#include "player.hpp"

Player::Player(double rad, double h, std::shared_ptr<Input>& in) {
    input = in;
    pos = in->getPos();
    c = {rad,h};
}

glm::vec3 Player::support(glm::vec3 dir) {
    if (dir.y >= 0) {
        dir.y = 0;
        if (glm::length(dir) == 0) {dir.x = 1;}
        dir = glm::normalize(dir) * glm::vec3(c.rad);
        dir.y = c.h/2;
        return pos + dir;
    }
    dir.y = 0;
    if (glm::length(dir) == 0) {dir.x = 1;}
    dir = glm::normalize(dir) * glm::vec3(c.rad);
    dir.y = -c.h/2;
    return pos + dir;
}

void Player::update() {
    pos = input->getPos();
}
