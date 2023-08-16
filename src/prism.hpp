#include "renderer.hpp"

class Prism : public Entity {
public:
    Prism(glm::vec3 pos, float rot, glm::vec3 axis, glm::vec3 dim);
    glm::mat4 model() override;
};

class PrismRenderer : public Renderer {
public:
    PrismRenderer(Shader program);
    void render(std::unique_ptr<Entity> e) override;
private:
    glm::mat2x3 ver2tex(std::unique_ptr<Entity> e);
    GLuint loadTex(std::string file);
    GLuint tex;
};
