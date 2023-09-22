#include <memory>
#include "entity.hpp"
#include "input.hpp"

struct Cyllinder {
    double rad = 0;
    double h = 0;
};

class Player : public Entity {
public:
    Player(double rad, double h, std::shared_ptr<Input>& in);
    void update(double dT);
    void move(glm::vec3 p) {
        input->setPos(input->getPos()+p);
        pos = input->getPos();
        if (p != glm::vec3(0)) {
            if (glm::dot(glm::normalize(p),input->getUp()) > 0.5) {grounded = true;}
        }
    }

    glm::vec3 velocity = glm::vec3(0);
private:
    glm::vec3 support(glm::vec3 dir) override;

    Cyllinder c;
    std::shared_ptr<Input> input;

    const double terminalVelocity = 200.0;
    double gravity = 30.0;
    bool grounded = false;
};
