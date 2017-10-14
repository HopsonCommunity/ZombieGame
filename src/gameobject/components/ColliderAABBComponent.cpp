#include "ColliderAABBComponent.h"

#include "RigidBodyComponent.h"
#include "TransformComponent.h"

#include "../GameObject.h"

#include "../../systems/ColliderSpace.h"
#include "../../state/GameState.h"

#include <functional>

unsigned int ColliderAABBComponent::ID = 7;

ColliderAABBComponent::ColliderAABBComponent(GameObject& owner, nlohmann::json json) 
:   Component(owner) 
{
    m_collider = AABBCollider(
        -sf::Vector2f(json["neg_offset_position"][0], json["neg_offset_position"][1]), 
        sf::Vector2f(json["dimension"][0], json["dimension"][1])
    );
}

ColliderAABBComponent::ColliderAABBComponent(GameObject& owner, sf::Vector2f offset_position, sf::Vector2f dimension)
:   Component(owner)
,   m_collider(AABBCollider(offset_position, dimension)) {}

ColliderAABBComponent::~ColliderAABBComponent()
{
    m_owner.getOwningState().getColliderSpace()->remove(m_transform);
}

void ColliderAABBComponent::setup()
{
    m_transform = m_owner.getComponent<TransformComponent>();
    m_owner.getOwningState().getColliderSpace()->insert({ 
        m_transform, 
        m_owner.getComponent<RigidBodyComponent>(), 
        &m_collider, 
        std::function<void(CollisionInfo&)>([&] (CollisionInfo& c)  { m_owner.onCollision(c);   }),
        std::function<void(TriggerInfo&)>([&] (TriggerInfo& t)      { m_owner.onTrigger(t);     }) 
    });
}

void ColliderAABBComponent::update(sf::Time const& )
{}

void ColliderAABBComponent::fixed_update(sf::Time const& )
{}

void ColliderAABBComponent::render(sf::RenderTarget& renderTarget) 
{
    if (ColliderAABBComponent::collider_wire_frame) 
    {
        auto ns = m_collider.getNormals();
        auto ps = m_collider.getPoints();

        sf::Vertex vs[5];
        int i = 0;
        for (auto const& p : ps) 
        {
            vs[i].position = p + m_transform->position;
            vs[i].color = sf::Color::Green;
            i++;
        }
        vs[4].position = m_collider.getPoints()[0] + m_transform->position;
        vs[4].color = sf::Color::Green;
        renderTarget.draw(vs, 5, sf::PrimitiveType::LinesStrip);

        sf::Vertex vns[4];
        i = 0;
        for (auto const& n : ns) 
        {
            sf::Vector2f start = m_transform->position;
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
    return std::make_unique<ColliderAABBComponent>(newGameObject, m_collider.getOrigin(), m_collider.getDimension());
}

float ColliderAABBComponent::left() const 
{
    return m_transform->position.x + m_collider.getOrigin().x;    
}

float ColliderAABBComponent::right() const
{
    return m_transform->position.x + m_collider.getOrigin().x + m_collider.getDimension().x;    
}

float ColliderAABBComponent::top() const
{
    return m_transform->position.y + m_collider.getOrigin().y;    
}

float ColliderAABBComponent::bottom() const
{
    return m_transform->position.y + m_collider.getOrigin().y + m_collider.getDimension().y;    
}

float ColliderAABBComponent::width() const
{
    return m_collider.getDimension().x;
}

float ColliderAABBComponent::height() const
{
    return m_collider.getDimension().y;
}

