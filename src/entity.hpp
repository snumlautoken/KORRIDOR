#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity {
public:
    virtual glm::mat4 model() {return glm::mat4(1.0f); };
protected:
    glm::vec3 pos;
    glm::vec3 axis;
    glm::vec3 scale;
    float rot;
};
