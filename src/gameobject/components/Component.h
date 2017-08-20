#pragma once

#include <memory>

namespace sf
{
	class RenderWindow;
	class Time;
}

namespace GameObject
{
	class GameObject;

	class Component
	{
	public:
		Component(GameObject& owner)
			: m_owner(owner)
		{

		}

		virtual void setup() = 0;
		virtual void update(sf::Time& deltaTime) = 0;
		virtual void fixedUpdate(sf::Time& deltaTime) = 0;
		virtual void render(sf::RenderWindow& renderWindow) = 0;

		virtual std::unique_ptr<Component> clone(GameObject& newGameObject) = 0;
	protected:
		GameObject& m_owner;
	};
}
