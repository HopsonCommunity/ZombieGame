#pragma once

#include "Component.h"

#include <json.hpp>

class TestComponent : public Component
{
    public:
        TestComponent(GameObject& owner, nlohmann::json json);
        TestComponent(GameObject& owner, float someVal);

        void setup() override;
        void update(const sf::Time& deltaTime) override;
        void fixed_update(const sf::Time &deltaTime) override;
        void render(sf::RenderTarget& renderTarget) override;
        std::unique_ptr<Component> clone(GameObject& newGameObject) override;

        static unsigned ID;

        float SomeVal;
};
