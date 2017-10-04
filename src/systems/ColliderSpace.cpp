#include "ColliderSpace.h"

#include "../gameobject/components/ColliderAABBComponent.h"

#include <algorithm>
#include <iostream>

void ColliderSpace::insert(ColliderAABBComponent& collider) {
    m_colliders.push_back(&collider);
}

void ColliderSpace::remove(ColliderAABBComponent& collider) {
    m_colliders.erase(std::remove(m_colliders.begin(), m_colliders.end(), &collider), m_colliders.end());
}

void ColliderSpace::update(sf::Time const& time)
{
    for (auto it0 = m_colliders.begin(); it0 != m_colliders.end(); ++it0) 
    {
        for (auto it1 = it0 + 1; it1 != m_colliders.end(); ++it1) 
        {
            auto& c0 = **it0;
            auto& c1 = **it1;
            float dl = c1.right() - c0.left();
            float dr = c0.right() - c1.left();
            float dt = c1.bottom() - c0.top();
            float db = c0.bottom() - c1.top();

            if (dl > 0 && dr > 0 && db > 0 && dt > 0) // Collision
            {
                std::cout << "Collision " << dl << ", " << dr << ", " << dt << ", " << db << std::endl;
                if (dl < c1.width() - c0.width())
                {
                    if (dt < c1.height() - c0.height())
                    {
                        if (dt < dl)
                            c0.transform->position.y += dt;
                        else
                            c0.transform->position.x += dl;
                    }
                    else if (db < c0.height())
                    {
                        if (db < dl)
                            c0.transform->position.y -= db;
                        else
                            c0.transform->position.x += dl;
                    } 
                    else
                    {
                        c0.transform->position.x += dl;
                    }
                }
                else if (dr < c0.width())
                {
                    if (dt < c1.height() - c0.height())
                    {
                        if (dt < dr)
                            c0.transform->position.y += dt;
                        else
                            c0.transform->position.x -= dr;
                    }
                    else if (db < c0.height())
                    {
                        if (db < dr)
                            c0.transform->position.y -= db;
                        else
                            c0.transform->position.x -= dr;
                    }
                    else
                    {
                        c0.transform->position.x -= dr;
                    }
                }
                else if (dt < c1.height() - c0.height())
                {
                    c0.transform->position.y += dt;
                }
                else if (db < c0.height())
                {
                    c0.transform->position.y -= db;
                }
            }
        }
    }    
}

bool ColliderSpace::checkAABBCollision(ColliderAABBComponent const& c0, ColliderAABBComponent const& c1)
{
    return !(
        c0.left() > c1.right() ||
        c0.right() < c1.left() ||
        c0.top() > c1.bottom() ||
        c0.bottom() < c1.top()
    );
}