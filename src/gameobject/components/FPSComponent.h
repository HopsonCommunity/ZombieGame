#pragma once

#include "Component.h"

#include <SFML/Graphics.hpp>

#include <json.hpp>

class GameObject;
class CameraComponent;

class FPSComponent : public Component
{
    static constexpr int AVERAGE_FPS_COUNT = 60;

public:

    FPSComponent(GameObject& owner, nlohmann::json json);
    FPSComponent(GameObject& owner, sf::Text const& text, sf::Vector2f const& position);

    virtual void setup();
    virtual void update(const sf::Time& deltaTime);
    virtual void fixed_update(const sf::Time &deltaTime);
    virtual void render(RenderingManager& renderTarget);

    virtual std::unique_ptr<Component> clone(GameObject& newGameObject);

    static unsigned int ID; 

    sf::Text text;
    sf::Vector2f position;
    int prev_fps[AVERAGE_FPS_COUNT];

    CameraComponent* camera;
};