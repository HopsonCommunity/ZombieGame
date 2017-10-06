#include "ColliderSpace.h"

#include "../gameobject/components/ColliderAABBComponent.h"
#include "../gameobject/components/RigidBodyComponent.h"

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
                resolveCollision(c0, c1, {dx_neg ? -dx_abs : dx_abs, 0});
            else
                resolveCollision(c0, c1, {0, dy_neg ? -dy_abs : dy_abs});
        }
        else
        {
            resolveCollision(c0, c1, {0, dy_neg ? -dy_abs : dy_abs});
        }
    }
}

void ColliderSpace::resolveCollision(ColliderAABBComponent& c0, ColliderAABBComponent& c1, sf::Vector2f const& movement)
{
    auto rb0 = c0.rigidbody;
    auto rb1 = c1.rigidbody;
    if (rb0 && rb1) 
    {
        bool c0_static = rb0->is_static;
        bool c1_static = rb1->is_static;

        float factor0 = (c0_static ? 0 : (c1_static ? 1 : (1 - rb0->mass / (rb0->mass + rb1->mass))));
        float factor1 = (c1_static ? 0 : (c0_static ? 1 : (1 - rb1->mass / (rb0->mass + rb1->mass))));
        
        constexpr float epsilon = 0.01; 
        assert(factor0 + factor1 > 1 - epsilon || factor0 + factor1 < 1 + epsilon);

        c0.transform->position += movement * factor0;
        c1.transform->position -= movement * factor1;
        // onCollision
    }
    // else
    //  onTrigger
}