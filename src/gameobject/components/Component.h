#pragma once

#include "../../util/Renderer.h"
#include "../../util/Renderer.h"

#include <memory>
#include <SFML/Graphics.hpp>

class GameObject;
class CollisionInfo;
class TriggerInfo;
class DebugRenderer;

class Component
{
    public:
        Component(GameObject& owner)
            : m_owner(owner)
        { }

        virtual void setup() = 0;
        virtual void update(const sf::Time& deltaTime) = 0;
        virtual void fixed_update(const sf::Time &deltaTime) = 0;
        virtual void render(Renderer& renderTarget) = 0;

        virtual std::unique_ptr<Component> clone(GameObject& newGameObject) = 0;

        virtual void onCollision(CollisionInfo&) {}
        virtual void onTrigger(TriggerInfo&) {}
        
    protected:
        GameObject& m_owner;
};
