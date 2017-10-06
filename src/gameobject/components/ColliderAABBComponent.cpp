#include "ColliderAABBComponent.h"
#include "../GameObject.h"
#include "../../state/GameState.h"

unsigned int ColliderAABBComponent::ID = 7;

ColliderAABBComponent::ColliderAABBComponent(GameObject& owner, nlohmann::json json) 
    : Component(owner) 
{
    dimension = sf::Vector2f(json["dimension"][0], json["dimension"][1]);
    offset_position = -sf::Vector2f(json["neg_offset_position"][0], json["neg_offset_position"][1]);
    constraint = json.count("static") ? ColliderAABBComponent::Constraint::Static : ColliderAABBComponent::Constraint::Dynamic;
    mass = json.count("mass") ? static_cast<float>(json["mass"]) : 1;    
}

ColliderAABBComponent::ColliderAABBComponent(GameObject& owner, sf::Vector2f offset_position, sf::Vector2f dimension, ColliderAABBComponent::Constraint constraint, float mass)
    : Component(owner), offset_position(offset_position), dimension(dimension), constraint(constraint), mass(mass)
{

}

ColliderAABBComponent::~ColliderAABBComponent()
{
    m_owner.getOwningState().getColliderSpace()->remove(*this);
}

void ColliderAABBComponent::setup()
{
    transform = m_owner.getComponent<TransformComponent>();
    m_owner.getOwningState().getColliderSpace()->insert(*this);
}

void ColliderAABBComponent::update(sf::Time const& time)
{

}

void ColliderAABBComponent::fixed_update(sf::Time const& time)
{

}

void ColliderAABBComponent::render(sf::RenderTarget& renderTarget) 
{
    if (ColliderAABBComponent::collider_wire_frame) {
        sf::RectangleShape box(dimension);
        box.setPosition(transform->position + offset_position);
        box.setOutlineColor(sf::Color::Green);
        box.setOutlineThickness(1);
        box.setFillColor(sf::Color(0, 0, 0, 0));
        renderTarget.draw(box);
    }
}

std::unique_ptr<Component> ColliderAABBComponent::clone(GameObject& newGameObject)
{
    return std::make_unique<ColliderAABBComponent>(newGameObject, offset_position, dimension, constraint, mass);
}

float ColliderAABBComponent::left() const 
{
    return transform->position.x + offset_position.x;    
}

float ColliderAABBComponent::right() const
{
    return transform->position.x + offset_position.x + dimension.x;    
}

float ColliderAABBComponent::top() const
{
    return transform->position.y + offset_position.y;    
}

float ColliderAABBComponent::bottom() const
{
    return transform->position.y + offset_position.y + dimension.y;    
}

float ColliderAABBComponent::width() const
{
    return dimension.x;
}

float ColliderAABBComponent::height() const
{
    return dimension.y;
}

