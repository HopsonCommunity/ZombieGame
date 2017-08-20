#pragma once

#include "components/Component.h"

#include <memory>
#include <unordered_map>

namespace sf
{
	class Time;
	class RenderWindow;
}

namespace GameState
{
	class GameState;
}

namespace GameObject
{
	class GameObject
	{
	public:
		GameObject(GameState::GameState& gamestate, unsigned int id);

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
		void update(sf::Time& deltaTime);
		void render(sf::RenderWindow& renderWindow);

		std::unique_ptr<GameObject> clone(GameState::GameState& owningState, unsigned int id);

	private:
		std::unordered_map<unsigned int, std::unique_ptr<Component>> m_components;
		GameState::GameState& m_owningState;
		unsigned int m_id;
	};
}
