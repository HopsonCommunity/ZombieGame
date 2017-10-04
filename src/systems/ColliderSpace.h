#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

class ColliderAABBComponent;

class ColliderSpace {
public:

    void insert(ColliderAABBComponent& collider);
    void remove(ColliderAABBComponent& collider);

    void update(sf::Time const& time);
    
private:

    void AABBCollision(ColliderAABBComponent& c0, ColliderAABBComponent& c1);
    void resolveCollision(ColliderAABBComponent& c0, ColliderAABBComponent& c1, sf::Vector2f const& movement);
    
    std::vector<ColliderAABBComponent*> m_colliders;
};