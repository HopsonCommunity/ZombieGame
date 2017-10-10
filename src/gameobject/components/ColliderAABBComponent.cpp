#include "ColliderAABBComponent.h"

#include "../GameObject.h"
#include "../../state/GameState.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"

unsigned int ColliderAABBComponent::ID = 7;

ColliderAABBComponent::ColliderAABBComponent(GameObject& owner, nlohmann::json json) 
    : Component(owner) 
{
    collider = AABBCollider(
        -sf::Vector2f(json["neg_offset_position"][0], json["neg_offset_position"][1]), 
        sf::Vector2f(json["dimension"][0], json["dimension"][1]));
}

ColliderAABBComponent::ColliderAABBComponent(GameObject& owner, sf::Vector2f offset_position, sf::Vector2f dimension)
    : Component(owner), collider(AABBCollider(offset_position, dimension))
{

}

ColliderAABBComponent::~ColliderAABBComponent()
{
    m_owner.getOwningState().getColliderSpace()->remove(transform);
}

void ColliderAABBComponent::setup()
{
    transform = m_owner.getComponent<TransformComponent>();
    m_owner.getOwningState().getColliderSpace()->insert({ transform, m_owner.getComponent<RigidBodyComponent>(), &collider });
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
        auto ns = collider.getNormals();
        auto ps = collider.getPoints();

        sf::Vertex vs[5];
        int i = 0;
        for (auto const& p : ps) {
            vs[i].position = p + transform->position;
            vs[i].color = sf::Color::Green;
            i++;
        }
        vs[4].position = collider.getPoints()[0] + transform->position;
        vs[4].color = sf::Color::Green;
        renderTarget.draw(vs, 5, sf::PrimitiveType::LinesStrip);

        sf::Vertex vns[4];
        i = 0;
        for (auto const& n : ns) {
            sf::Vector2f start = transform->position;
            vns[i].position = start;
            vns[i+1].position = start + n*10.f;
            vns[i].color = sf::Color::Magenta;
            vns[i+1].color = sf::Color::Magenta;
            i += 2;
        }
        renderTarget.draw(vns, 8, sf::PrimitiveType::Lines);
    }
}

std::unique_ptr<Component> ColliderAABBComponent::clone(GameObject& newGameObject)
{
    return std::make_unique<ColliderAABBComponent>(newGameObject, collider.getOrigin(), collider.getDimension());
}

float ColliderAABBComponent::left() const 
{
    return transform->position.x + collider.getOrigin().x;    
}

float ColliderAABBComponent::right() const
{
    return transform->position.x + collider.getOrigin().x + collider.getDimension().x;    
}

float ColliderAABBComponent::top() const
{
    return transform->position.y + collider.getOrigin().y;    
}

float ColliderAABBComponent::bottom() const
{
    return transform->position.y + collider.getOrigin().y + collider.getDimension().y;    
}

float ColliderAABBComponent::width() const
{
    return collider.getDimension().x;
}

float ColliderAABBComponent::height() const
{
    return collider.getDimension().y;
}

