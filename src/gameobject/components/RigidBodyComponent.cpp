#include "RigidBodyComponent.h"

#include "../GameObject.h"
#include "TransformComponent.h"

unsigned int RigidBodyComponent::ID = 8;

RigidBodyComponent::RigidBodyComponent(GameObject& owner, nlohmann::json json) : Component(owner) {
    velocity = sf::Vector2f{ json["velocity"][0], json["velocity"][1] };
    is_static = json.count("static") > 0 && static_cast<bool>(json["static"]);
    mass = json.count("mass") ? static_cast<float>(json["mass"]) : 1;    
}

RigidBodyComponent::RigidBodyComponent(GameObject& owner, sf::Vector2f const& velocity, float mass, bool is_static)
    : Component(owner), velocity(velocity), mass(mass), is_static(is_static) {}

void RigidBodyComponent::setup() {
    transform = m_owner.getComponent<TransformComponent>();
}

void RigidBodyComponent::update(const sf::Time& deltaTime) {
    transform->position += velocity;
}

void RigidBodyComponent::fixed_update(const sf::Time &deltaTime) {

}

void RigidBodyComponent::render(sf::RenderTarget& renderTarget) {

}

std::unique_ptr<Component> RigidBodyComponent::clone(GameObject& newGameObject) {
    return std::make_unique<RigidBodyComponent>(newGameObject, velocity, mass, is_static);
}

void RigidBodyComponent::addForce(sf::Vector2f const& force) {
    if (!is_static)
        velocity += force / mass;
}
