#include "graphics.hpp"
#include "player.hpp"
#include <vector>
#include <list>
#include <map>
#include <typeinfo>

typedef std::shared_ptr<Entity> Entity_ptr;

class Scene {
public:
    Scene(std::shared_ptr<Graphics> gr, Player p);
    std::vector<Prism> prisms;
    std::unique_ptr<Skybox> skybox;
    Player player;

    template<typename T>
    void addEntity(T e) {
        std::string className = typeid(e).name();
        entities[typeid(e).name()].push_back(std::make_shared<T>(e));
    }

    void playerCollision();
    void render();
private:
    std::shared_ptr<Graphics> gr_ptr;
    std::map<std::string, std::list<Entity_ptr>> entities;
};
