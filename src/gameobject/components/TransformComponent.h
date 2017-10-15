#pragma once

#include "Component.h"
#include <json.hpp>

class TransformComponent : public Component
{
public:
    TransformComponent(GameObject& owner, sf::Vector2f position, float rotation, bool renderTransform = false);
    TransformComponent(GameObject& owner, nlohmann::json json);

    void setup() override;
    void update(const sf::Time& deltaTime) override;
    void fixed_update(const sf::Time &deltaTime) override;
    void render(RenderingManager& renderTarget) override;
    std::unique_ptr<Component> clone(GameObject& newGameObject) override;

    static unsigned ID;

    sf::Vector2f position;
    double rotation;
    bool renderTransform = false;

    void lookAt(TransformComponent* target);
    sf::Vector2f front() const;
    sf::Vector2f right() const;
};
