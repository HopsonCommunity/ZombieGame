#include "GameObject.h"

#include "components/Component.h"

#include "../state/GameState.h"


namespace GameObject
{
	GameObject::GameObject(GameState::GameState& gamestate, unsigned int id)
        : m_id(id), m_owningState(gamestate) {
    }

	void GameObject::setup()
	{
		for (auto& it : m_components)
			it.second->setup();
	}

	void GameObject::update(sf::Time& deltaTime)
	{
		for (auto& it : m_components)
			it.second->update(deltaTime);
	}

	void GameObject::render(sf::RenderWindow& renderWindow)
	{
		for (auto& it : m_components)
			it.second->render(renderWindow);
	}

	std::unique_ptr<GameObject> GameObject::clone(GameState::GameState& owningState, unsigned int id)
	{
		auto clone = std::make_unique<GameObject>(owningState, id);

		for (auto& it : m_components)
			clone->m_components[it.first] = it.second->clone(*clone);

		clone->setup();

		return clone;
	}
}
