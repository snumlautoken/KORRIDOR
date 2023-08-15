#include "graphics.hpp"

int main() {

    Graphics graphics(1000,1000);

    while(!glfwWindowShouldClose(graphics.window)) {
        graphics.render();
    }
    return 0;
}
