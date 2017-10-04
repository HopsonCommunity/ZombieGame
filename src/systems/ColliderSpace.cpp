#include "ColliderSpace.h"

#include "../gameobject/components/ColliderAABBComponent.h"

#include <algorithm>
#include <cassert>

void ColliderSpace::insert(ColliderAABBComponent& collider) {
    m_colliders.push_back(&collider);
}

void ColliderSpace::remove(ColliderAABBComponent& collider) {
    m_colliders.erase(std::remove(m_colliders.begin(), m_colliders.end(), &collider), m_colliders.end());
}

void ColliderSpace::update(sf::Time const& time)
{
    for (auto it0 = m_colliders.begin(); it0 != m_colliders.end(); ++it0) 
        for (auto it1 = it0 + 1; it1 != m_colliders.end(); ++it1) 
            AABBCollision(**it0, **it1);
}

void ColliderSpace::AABBCollision(ColliderAABBComponent& c0, ColliderAABBComponent& c1)
{
    float dl = c1.right() - c0.left();
    float dr = c0.right() - c1.left();
    float dt = c1.bottom() - c0.top();
    float db = c0.bottom() - c1.top();

    if (dl > 0 && dr > 0 && db > 0 && dt > 0) // Collision
    {
        bool dx_neg = false;
        bool dy_neg = false;
        float dx_abs = 0;
        float dy_abs = 0;
        if (dl < c1.width() - c0.width())
        {
            dx_abs = dl;
        }
        else if (dr < c0.width())
        {
            dx_abs = dr;
            dx_neg = true;
        }

        if (dt < c1.height() - c0.height())
        {
            dy_abs = dt;
        }
        else if (db < c0.height())
        {
            dy_abs = db;
            dy_neg = true;
        }

        if (dx_abs != 0)
        {
            if (dy_abs == 0 || dx_abs < dy_abs)
//                c0.transform->position.x += dx_neg ? -dx_abs : dx_abs;
                resolveCollision(c0, c1, {dx_neg ? -dx_abs : dx_abs, 0});
            else
                resolveCollision(c0, c1, {0, dy_neg ? -dy_abs : dy_abs});
//                c0.transform->position.y += dy_neg ? -dy_abs : dy_abs;                        
        }
        else
        {
            resolveCollision(c0, c1, {0, dy_neg ? -dy_abs : dy_abs});
//            c0.transform->position.y += dy_neg ? -dy_abs : dy_abs;                        
        }
    }
}

void ColliderSpace::resolveCollision(ColliderAABBComponent& c0, ColliderAABBComponent& c1, sf::Vector2f const& movement)
{
    bool c0_static = c0.constraint == ColliderAABBComponent::Constraint::Static;
    bool c1_static = c1.constraint == ColliderAABBComponent::Constraint::Static;

    float factor0 = (c0_static ? 0 : (c1_static ? 1 : (1 - c0.mass / (c0.mass + c1.mass))));
    float factor1 = (c1_static ? 0 : (c0_static ? 1 : (1 - c1.mass / (c0.mass + c1.mass))));
    
    constexpr float epsilon = 0.01; 
    assert(factor0 + factor1 > 1 - epsilon || factor0 + factor1 < 1 + epsilon);

    c0.transform->position += movement * factor0;
    c1.transform->position -= movement * factor1;
}