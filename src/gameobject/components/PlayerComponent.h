#pragma once

#include <json.hpp>
#include "Component.h"
#include "TransformComponent.h"

#include "../../systems/ColliderSpace.h"
#include <iostream>

class PlayerComponent : public Component
{
public:
    PlayerComponent(GameObject& owner, nlohmann::json json);
    PlayerComponent(GameObject& owner, float speed);

    void setup() override;
    void update(const sf::Time& deltaTime) override;
    void fixed_update(const sf::Time &deltaTime) override;
    void render(RenderingManager& renderTarget) override;
    std::unique_ptr<Component> clone(GameObject& newGameObject) override;
    
    static unsigned ID;

    float speed;

    TransformComponent* transform;
    TransformComponent* mouse;
};