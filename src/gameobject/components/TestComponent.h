#include "Component.h"

#include <json.hpp>

class TestComponent : public Component
{
    public:
        TestComponent(GameObject& owner, nlohmann::json json);
        TestComponent(GameObject& owner, float someVal);

        void setup() override;
        void update(sf::Time& deltaTime) override;
        void fixedUpdate(sf::Time& deltaTime) override;
        void render(sf::RenderWindow& window) override;
        std::unique_ptr<Component> clone(GameObject& newGameObject) override;

        static unsigned int ID;

        float SomeVal;
};
