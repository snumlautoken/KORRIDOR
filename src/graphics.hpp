#include "shader.hpp"
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <memory>
#include "renderer.hpp"
#include "input.hpp"

class Graphics {
public:
    Graphics(int width, int height);
    void render();

    GLFWwindow* window;
    std::unique_ptr<Input> input;
private:
    std::vector<std::unique_ptr<Renderer>> renderers;
};
