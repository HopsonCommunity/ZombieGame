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

void TestComponent::update(sf::Time& deltaTime)
{

}

void TestComponent::fixedUpdate(sf::Time& deltaTime)
{

}

void TestComponent::render(sf::RenderWindow& renderWindow)
{

}

std::unique_ptr<Component> TestComponent::clone(GameObject& newGameObject)
{
	return std::make_unique<TestComponent>(newGameObject, SomeVal);
}

