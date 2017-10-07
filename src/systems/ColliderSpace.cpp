#include "ColliderSpace.h"

#include "../gameobject/components/ColliderAABBComponent.h"
#include "../gameobject/components/RigidBodyComponent.h"

#include <algorithm>
#include <cassert>

Raycast::Raycast() : Raycast({0, 0}, {1, 0}) {}

Raycast::Raycast(sf::Vector2f const& start, sf::Vector2f const& direction, float distance) 
    : start(start), direction(direction), distance(distance) {}

bool Raycast::is_infinite() const {
    return distance == std::numeric_limits<float>::max();
}

sf::Vector2f Raycast::at(float d) const {
    return start + direction * d;
}

float Raycast::at_x(float d) const {
    return start.x + direction.x * d;
}

float Raycast::at_y(float d) const {
    return start.y + direction.y * d;
}

RaycastInfo::RaycastInfo() : RaycastInfo(nullptr, 0) {}

RaycastInfo::RaycastInfo(ColliderAABBComponent* collider, float distance) 
    : collider(collider), distance(distance) {}

RaycastInfo::operator bool() const {
    return collider != nullptr;
}

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

RaycastInfo ColliderSpace::raycast(Raycast const& r, std::unordered_set<ColliderAABBComponent*> const& ignored) {
    RaycastInfo info(nullptr, r.distance);
    for (auto& c : m_colliders) 
    {
        if (ignored.find(c) == ignored.end())
        {
            checkRaycastAABB(r, c, info);
            if (r.distance == 0)
                return info;
        }
    }
    return info;
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

void ColliderSpace::checkRaycastAABB(Raycast const& r, ColliderAABBComponent* c, RaycastInfo& info)
{
    float bottom = c->bottom();
    float right = c->right();
    float top = c->top();
    float left = c->left();
    if (r.direction.y != 0) 
    {
        {
            float d = (bottom - r.start.y) / r.direction.y;
            float x = r.at_x(d);
            if (d < info.distance && d >= 0 && d < r.distance && x >= left && x <= right)
            {
                info.distance = d;
                info.collider = c;
            }
        }
        {
            float d = (top - r.start.y) / r.direction.y;
            float x = r.at_x(d);
            if (d < info.distance && d >= 0 && d < r.distance && x >= left && x <= right)
            {
                info.distance = d;
                info.collider = c;
            }
        }
        {
            float d = (left - r.start.x) / r.direction.x;
            float y = r.at_y(d);
            if (d < info.distance && d >= 0 && d < r.distance && y >= top && y <= bottom)
            {
                info.distance = d;
                info.collider = c;
            }
        }
        {
            float d = (right - r.start.x) / r.direction.x;
            float y = r.at_y(d);
            if (d < info.distance && d >= 0 && d < r.distance && y >= top && y <= bottom)
            {
                info.distance = d;
                info.collider = c;
            }
        }
    }
    else
    {
        if (r.start.x >= left && r.start.x <= right)
        {
            info.distance = 0;
            info.collider = c;
        }
        else if (r.start.x > right && r.direction.x < 0)
        {
            float d = r.start.x - left;
            if (d < info.distance && d >= 0 && d < r.distance)
            {
                info.distance = d;
                info.collider = c;
            } 
        }
        else if (r.start.x < right && r.direction.x > 0)
        {
            float d = right - r.start.x;
            if (d < info.distance && d >= 0 && d < r.distance)
            {
                info.distance = d;
                info.collider = c;
            } 
        }
    }
}