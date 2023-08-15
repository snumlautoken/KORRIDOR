#include "renderer.hpp"
#include <vector>

class SkyboxRenderer : public Renderer {
public:
    SkyboxRenderer(Shader program);
    void render(std::unique_ptr<Entity> e) override;
private:
    void generateCube(float sideLen);
    GLuint loadCubemap(std::string dir);
    std::vector<float> vertices;
    std::vector<uint> indices;

    GLuint skyboxTex;
};
