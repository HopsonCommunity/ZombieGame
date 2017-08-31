#include "TestComponent.h"

#include <SFML/System.hpp>

#include <iostream>

unsigned TestComponent::ID = 0;

TestComponent::TestComponent(GameObject& owner, nlohmann::json json)
	: Component(owner)
{

}

TestComponent::TestComponent(GameObject& owner, float someVal)
	: Component(owner)
	, SomeVal(someVal)
{

}

void TestComponent::setup()
{

}

void TestComponent::update(const sf::Time& deltaTime)
{

}

void TestComponent::fixed_update(const sf::Time &deltaTime)
{

}

void TestComponent::render(sf::RenderTarget& renderTarget)
{

}

std::unique_ptr<Component> TestComponent::clone(GameObject& newGameObject)
{
	return std::make_unique<TestComponent>(newGameObject, SomeVal);
}

