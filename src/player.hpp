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
    void update();
    void move(glm::vec3 p) {
        input->setPos(input->getPos()+p);
        update();
    }
private:
    glm::vec3 support(glm::vec3 dir) override;
    Cyllinder c;
    std::shared_ptr<Input> input;
    bool isAirBorne = false;
};
