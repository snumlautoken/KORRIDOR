#include "shader.hpp"
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <memory>
#include "input.hpp"
#include "texture.hpp"
#include "prism.hpp"
#include "skybox.hpp"

class Graphics {
public:
    Graphics(int width, int height);
    void render();
    void draw(std::vector<Prism> prisms);
    void draw(Skybox skybox);
    GLFWwindow* window;
    std::shared_ptr<Input> input;
private:
    std::unique_ptr<SkyboxRenderer> sr;
};
