#pragma once

#include "../GameObject.h"
#include "Component.h"
#include "TransformComponent.h"

class CameraComponent : public Component
{
public:
    CameraComponent(GameObject& owner, nlohmann::json json);
    CameraComponent(GameObject& owner, sf::FloatRect dimensions);

    void setup() override;
    void update(const sf::Time& deltaTime) override;
    void fixed_update(const sf::Time &deltaTime) override;
    void render(sf::RenderTarget& renderTarget) override;
    std::unique_ptr<Component> clone(GameObject& newGameObject) override;

    static unsigned ID;

    sf::View view;
    sf::FloatRect dimensions;

    TransformComponent* transform;
};
