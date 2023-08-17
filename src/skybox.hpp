#include "shader.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Skybox {
public:
    Skybox(std::string dir);
    GLuint skyboxTex;
};

class SkyboxRenderer {
public:
    SkyboxRenderer(Shader program);
    void render(Skybox);
    Shader shaderProgram;
private:
    void generateCube(float sideLen);
    GLuint loadCubemap(std::string dir);
    std::vector<float> vertices;
    std::vector<uint> indices;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
};
