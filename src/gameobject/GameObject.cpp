#include "GameObject.h"

#include "components/Component.h"

#include "../state/GameState.h"
#include "../systems/ColliderSpace.h"

GameObject::GameObject(GameState& gamestate, unsigned id)
: m_id(id)
, m_owningState(gamestate) {
}

void GameObject::setup()
{
	for (auto& it : m_components)
		it.second->setup();
}

void GameObject::update(const sf::Time& deltaTime)
{
	for (auto& it : m_components)
		it.second->update(deltaTime);
}

void GameObject::fixed_update(const sf::Time& deltaTime)
{
	for (auto& it : m_components)
		it.second->fixed_update(deltaTime);
}

void GameObject::render(sf::RenderTarget& renderTarget)
{
	for (auto& it : m_components)
		it.second->render(renderTarget);
}

std::unique_ptr<GameObject> GameObject::clone(GameState& owningState, unsigned id)
{
	auto clone = std::make_unique<GameObject>(owningState, id);

	for (auto& it : m_components)
		clone->m_components[it.first] = it.second->clone(*clone);

	clone->setup();

	return clone;
}

void GameObject::onCollision(CollisionInfo& info) {
	for(auto& it : m_components)
		it.second->onCollision(info);
}

void GameObject::onTrigger(TriggerInfo& info) {
	for(auto& it : m_components)
		it.second->onTrigger(info);
}
