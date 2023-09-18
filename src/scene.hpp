#include "graphics.hpp"
#include "player.hpp"
#include <vector>
#include <list>
#include <map>
#include <typeinfo>

typedef std::shared_ptr<Entity> Entity_ptr;
typedef std::shared_ptr<Renderable> Renderable_ptr;

class Scene {
public:
    Scene(std::shared_ptr<Graphics> gr, Player p);
    std::vector<Prism> prisms;
    std::unique_ptr<Skybox> skybox;
    Player player;

    template<typename T>
    std::shared_ptr<T> addEntity(T e) {
        std::shared_ptr<T> e_ref = std::make_shared<T>(e);
        entities.push_back(e_ref);
        if (dynamic_cast<const Renderable*>(e_ref.get()) != nullptr) {
            renderables[typeid(e).name()].push_back(e_ref);
        }
        return e_ref;
    }

    void playerCollision();
    void render();
private:
    std::shared_ptr<Graphics> gr_ptr;
    std::list<Entity_ptr> entities;
    std::map<std::string, std::list<Renderable_ptr>> renderables;
};
