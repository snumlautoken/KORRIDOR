#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity {
public:
    virtual glm::vec3 support(glm::vec3 dir) = 0;

    glm::vec3 getScale() {return scale;};
    GLuint getTex() {return tex;};
    float getRot() {return rot;};
    glm::vec3 getPos() {return pos;};
    glm::vec3 getAxis() {return axis;};

    void setScale(glm::vec3 s) {scale = s;};
    void setTex(GLuint t) {tex = t;};
    void setRot(float r) {rot = r;};
    void setPos(glm::vec3 p) {pos = p;};
    void setAxis(glm::vec3 a) {axis = a;};


protected:
    glm::vec3 scale;
    GLuint tex;
    float rot;
    glm::vec3 pos;
    glm::vec3 axis;
};
