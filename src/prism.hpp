#include "texture.hpp"
#include "entity.hpp"
#include "shader.hpp"

class Prism : public Entity {
public:
    Prism(glm::vec3 pos, float rot, glm::vec3 axis, glm::vec3 dim, Texture texture);
    glm::mat4 getModel();

    glm::vec3 support(glm::vec3 dir) override;
    void setScale(glm::vec3 s) {scale = s; recalcModel();};
    void setTex(GLuint t) {tex = t; recalcModel();};
    void setRot(float r) {rot = r; recalcModel();};
    void setPos(glm::vec3 p) {pos = p; recalcModel();};
    void setAxis(glm::vec3 a) {axis = a; recalcModel();};

    bool scaleTex = true;
private:
    void recalcModel();
    void recalcVertices();
    glm::mat4 model;
    std::pair<glm::mat4,glm::mat4> vert;
};

class PrismRenderer {
public:
    PrismRenderer(Shader program);
    void render(Prism prism);
    Shader shaderProgram;
private:
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
};
