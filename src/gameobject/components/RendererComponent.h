#pragma once

#include <json.hpp>
#include "Component.h"
#include "TransformComponent.h"

class RendererComponent : public Component
{
public:
    RendererComponent(GameObject& owner, nlohmann::json json);
    RendererComponent(GameObject& owner, std::string textureName, sf::Vector2f offset_position, double offset_rotation,
                      sf::Vector2f scale, int zIndex);

    void setup() override;
    void update(const sf::Time& deltaTime) override;
    void fixed_update(const sf::Time &deltaTime) override;
    void render(Renderer& renderTarget) override;
    std::unique_ptr<Component> clone(GameObject& newGameObject) override;

    static unsigned ID;


    std::string textureName;
    sf::Sprite sprite;
    sf::Vector2f offset_position;
    double offset_rotation;
    sf::Vector2f scale;
    int zIndex = 0;

    TransformComponent* transform;
};
