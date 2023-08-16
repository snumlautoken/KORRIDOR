#include "entity.hpp"

class Player : public Entity {
public:
    Player(glm::vec3 pos, glm::vec3 dim);
private:
    bool isAirBorne = false;
};
