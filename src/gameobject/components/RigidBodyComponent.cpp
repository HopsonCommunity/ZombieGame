#include "RigidBodyComponent.h"

#include "TransformComponent.h"

#include "../GameObject.h"

unsigned int RigidBodyComponent::ID = 8;

RigidBodyComponent::RigidBodyComponent(GameObject& owner, nlohmann::json json) 
:   Component(owner) 
{
    velocity = sf::Vector2f{ json["velocity"][0], json["velocity"][1] };
    inv_mass = json.count("inv_mass") ? static_cast<float>(json["inv_mass"]) : 1;    
}

RigidBodyComponent::RigidBodyComponent(GameObject& owner, sf::Vector2f const& velocity, float inv_mass)
:   Component(owner)
,   velocity(velocity)
,   inv_mass(inv_mass) {}

void RigidBodyComponent::setup() 
{
    transform = m_owner.getComponent<TransformComponent>();
}

void RigidBodyComponent::update(const sf::Time& deltaTime) 
{
    transform->position += velocity * (deltaTime.asMilliseconds() / 1000.f);
}

void RigidBodyComponent::fixed_update(const sf::Time &) 
{}

void RigidBodyComponent::render(Renderer& )
{}

std::unique_ptr<Component> RigidBodyComponent::clone(GameObject& newGameObject) 
{
    return std::make_unique<RigidBodyComponent>(newGameObject, velocity, inv_mass);
}

void RigidBodyComponent::addForce(sf::Vector2f const& force) 
{
    velocity += force * inv_mass;
}
