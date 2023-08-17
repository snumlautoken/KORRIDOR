#include "texture.hpp"
#include "entity.hpp"
#include "shader.hpp"

class Prism : public Entity {
public:
    Prism(glm::vec3 pos, float rot, glm::vec3 axis, glm::vec3 dim, Texture texture);
    glm::mat4 model() override;
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
