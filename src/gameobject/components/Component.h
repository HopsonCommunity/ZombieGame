#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class GameObject;
class CollisionInfo;
class TriggerInfo;

class Component
{
    public:
        Component(GameObject& owner)
            : m_owner(owner)
        { }

        virtual void setup() = 0;
        virtual void update(const sf::Time& deltaTime) = 0;
        virtual void fixed_update(const sf::Time &deltaTime) = 0;
        virtual void render(sf::RenderTarget& renderTarget) = 0;

        virtual std::unique_ptr<Component> clone(GameObject& newGameObject) = 0;

        virtual void onCollision(CollisionInfo& info) {}
        virtual void onTrigger(TriggerInfo& info) {}
        
    protected:
        GameObject& m_owner;
};
