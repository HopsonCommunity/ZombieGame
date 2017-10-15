#pragma once

#include <json.hpp>

#include "Component.h"

class TransformComponent;

class AnimationComponent : public Component
{
public:
    AnimationComponent(GameObject& owner, nlohmann::json json);
    AnimationComponent  (GameObject& owner, float framesPerSecond, int currentFrameID, std::string textureName,
                         sf::Vector2f offset_position, double offset_rotation, sf::Vector2f scale, int frame_width);

    void setup() override;
    void update(const sf::Time& deltaTime) override;
    void fixed_update(const sf::Time &deltaTime) override;
    void render(RenderingManager& renderTarget) override;
    std::unique_ptr<Component> clone(GameObject& newGameObject) override;

    static unsigned ID;

    float FrameTime=1000.f;
    int CurrentFrameID;
    int MaxFrameID = 0;
    std::string textureName;
    sf::Sprite sprite;
    sf::Vector2f offset_position;
    double offset_rotation;
    sf::Vector2f scale;
    int frame_width;
    sf::IntRect rectSourceSprite;
    sf::Clock clock;
    int frame_direction;

    TransformComponent* transform;
};
