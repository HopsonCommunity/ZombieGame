#pragma once

#include "Collider/SAT_Collider.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <limits>
#include <unordered_set>
#include <functional>

class ColliderAABBComponent;
class TransformComponent;
class RigidBodyComponent;

struct CollisionInfo {
    TransformComponent* other;
    SAT_Collider* other_collider;

    sf::Vector2f resolveMovement;
};

struct TriggerInfo {
    TransformComponent* other;
    SAT_Collider* other_collider;
};

struct Raycast {
    static constexpr float max_distance = 100000; // to avoid overflow... // std::numeric_limits<float>::max() 
    Raycast();
    Raycast(sf::Vector2f const& start, sf::Vector2f const& direction, float distance = max_distance);

    bool is_infinite() const;
    sf::Vector2f at(float d) const;
    float at_x(float d) const;
    float at_y(float d) const;
    
    sf::Vector2f start, direction;
    float distance;
};

struct ColliderOwner {
    TransformComponent* tf;
    RigidBodyComponent* rb;
    SAT_Collider* collider;

    std::function<void(CollisionInfo&)> onCollision;
    std::function<void(TriggerInfo&)> onTrigger;
    
    bool operator == (ColliderOwner const& o) const;
    bool operator != (ColliderOwner const& o) const;
};

struct RaycastInfo {
    RaycastInfo();
    RaycastInfo(TransformComponent* other, float distance);

    operator bool() const;

    TransformComponent* other;
    float distance;
};

class ColliderSpace {
public:

    void insert(ColliderOwner const& colider);
    void remove(ColliderOwner const& collider);
    void remove(TransformComponent* tf);
    void updateRigidBody(TransformComponent* tf, RigidBodyComponent* rb);

    void update(sf::Time const& time);

    RaycastInfo raycast(Raycast const& r, std::unordered_set<TransformComponent*> const& ignored = {});
    
private:

    void checkCollision(ColliderOwner& c0, ColliderOwner& c1);
    void checkRaycastCollision(Raycast const& r, ColliderOwner& c, RaycastInfo& info);
    void resolveCollision(ColliderOwner& c0, ColliderOwner& c1, sf::Vector2f const& direction);
    float getMTV(Projection const& p0, Projection const& p1) const;
        
    std::vector<ColliderOwner> m_colliders;
};