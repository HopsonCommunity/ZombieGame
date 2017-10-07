#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <limits>
#include <unordered_set>

class ColliderAABBComponent;

struct Raycast {
    static constexpr float max_distance = 10000; // std::numeric_limits<float>::max() 
    Raycast();
    Raycast(sf::Vector2f const& start, sf::Vector2f const& direction, float distance = max_distance);

    bool is_infinite() const;
    sf::Vector2f at(float d) const;
    float at_x(float d) const;
    float at_y(float d) const;
    
    sf::Vector2f start, direction;
    float distance;
};

struct RaycastInfo {
    RaycastInfo();
    RaycastInfo(ColliderAABBComponent* collider, float distance);

    operator bool() const;

    ColliderAABBComponent* collider;
    float distance;
};

class ColliderSpace {
public:

    void insert(ColliderAABBComponent& collider);
    void remove(ColliderAABBComponent& collider);

    void update(sf::Time const& time);

    RaycastInfo raycast(Raycast const& r, std::unordered_set<ColliderAABBComponent*> const& ignored = {});
    
private:

    void checkRaycastAABB(Raycast const& r, ColliderAABBComponent* c, RaycastInfo& info);
    void AABBCollision(ColliderAABBComponent& c0, ColliderAABBComponent& c1);
    void resolveCollision(ColliderAABBComponent& c0, ColliderAABBComponent& c1, sf::Vector2f const& movement);
    
    std::vector<ColliderAABBComponent*> m_colliders;
};