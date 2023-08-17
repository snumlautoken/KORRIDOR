#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct AABB {
    glm::vec3 o,l,r,u;
};

class Entity {
public:
    virtual glm::mat4 model() { return glm::mat4(1.0f); };
    glm::vec3 scale;
    GLuint tex;
    AABB box;
protected:
    glm::vec3 pos;
    glm::vec3 axis;
    float rot;
};
