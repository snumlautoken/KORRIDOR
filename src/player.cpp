#include "player.hpp"

Player::Player(double rad, double h, std::shared_ptr<Input>& in) {
    input = in;
    pos = in->getPos();
    c = {rad,h};
}

glm::vec3 Player::support(glm::vec3 dir) {
    double oldY = dir.y;
    dir.y = 0;
    double maxVal = FLT_MIN;
    int maxDeg = 0;
    for (int i = 0; i < 360; i += 20) {
        double val = dir.x*cos(i*M_PI/180) + dir.z*sin(i*M_PI/180);
        if (val > maxVal) {
            maxDeg = i;
        }
    }
    dir.x = c.rad*cos(maxDeg*M_PI/180);
    dir.z = c.rad*sin(maxDeg*M_PI/180);

    dir.y = oldY >= 0 ? 0.1 : -c.h;

    return pos + dir;
}

void Player::update() {
    pos = input->getPos();
}
