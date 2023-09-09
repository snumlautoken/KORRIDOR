#include "graphics.hpp"
#include "player.hpp"
#include <vector>

class Scene {
public:
    Scene(std::shared_ptr<Graphics> gr);
    std::vector<Prism> prisms;
    std::unique_ptr<Skybox> skybox;
    void render();
private:
    std::shared_ptr<Graphics> gr_ptr;
};
