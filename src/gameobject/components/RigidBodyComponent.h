#pragma once

#include <json.hpp>

#include "Component.h"

class GameObject;
class TransformComponent;

class RigidBodyComponent : public Component {
public:

    RigidBodyComponent(GameObject& owner, nlohmann::json json);
    RigidBodyComponent(GameObject& owner, sf::Vector2f const& velocity, float mass, bool is_static);

    virtual void setup();
    virtual void update(const sf::Time& deltaTime);
    virtual void fixed_update(const sf::Time &deltaTime);
    virtual void render(sf::RenderTarget& renderTarget);

    virtual std::unique_ptr<Component> clone(GameObject& newGameObject);

    void addForce(sf::Vector2f const& force);

    TransformComponent* transform;

    sf::Vector2f velocity;
    float mass;
    bool is_static;

    static unsigned int ID; 

};