#pragma once

#include <memory>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "components/Component.h"

class GameState;

class GameObject
{
    public:
        GameObject(GameState& gamestate, unsigned int id);

        template<typename T>
        void addComponent(std::unique_ptr<Component> component)
        {
            m_components[T::ID] = std::move(component);
        }

        template<typename T>
        void removeComponent()
        {
            m_components.erase(T::ID);
        }

        template<typename T>
        T* getComponent()
        {
            unsigned int id = T::ID;
            auto it = m_components.find(id);
            if (it != m_components.end())
                return static_cast<T*>(it->second.get());

            return nullptr;
        }

        void setup();
        void update(const sf::Time& deltaTime);
        void fixed_update(const sf::Time& deltaTime);
        void render(sf::RenderTarget& renderTarget);

        std::unique_ptr<GameObject> clone(GameState& owningState, unsigned int id);

        GameState& getOwningState() { return m_owningState;}

    private:
        std::unordered_map<unsigned int, std::unique_ptr<Component>> m_components;
        GameState& m_owningState;
        unsigned int m_id;
};

