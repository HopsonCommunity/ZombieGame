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

    bool checkAABBCollision(ColliderAABBComponent const& c0, ColliderAABBComponent const& c1);
     
    std::vector<ColliderAABBComponent*> m_colliders;
};