#pragma once

#include <json.hpp>
#include "Component.h"
#include "TransformComponent.h"

class ColliderAABBComponent : public Component
{
public:
    ColliderAABBComponent(GameObject& owner, nlohmann::json json);
    ColliderAABBComponent(GameObject& owner, sf::Vector2f offset_position, sf::Vector2f dimension);
    ~ColliderAABBComponent();

    void setup() override;
    void update(const sf::Time& deltaTime) override;
    void fixed_update(const sf::Time &deltaTime) override;
    void render(sf::RenderTarget& renderTarget) override;
    std::unique_ptr<Component> clone(GameObject& newGameObject) override;

    static unsigned ID;

    float left() const;
    float right() const;
    float top() const;
    float bottom() const;

    float width() const;
    float height() const;

    TransformComponent* transform;
    
private:

    sf::Vector2f offset_position;
    sf::Vector2f dimension;
};