#include <json.hpp>
#include "CameraComponent.h"
#include "../GameObject.h"
#include "../../state/GameState.h"
#include "../../Game.h"
#include "TransformComponent.h"

unsigned CameraComponent::ID = 5;

CameraComponent::CameraComponent(GameObject &owner, nlohmann::json json)
        : Component(owner)
{
    dimensions = sf::FloatRect(json["position"][0], json["position"][1], json["resolution"][0], json["resolution"][1]);
    view = sf::View(dimensions);
}

CameraComponent::CameraComponent(GameObject &owner, sf::FloatRect dimensions)
        : Component(owner), view(dimensions)
{}

void CameraComponent::setup()
{
    transform = m_owner.getComponent<TransformComponent>();
}

void CameraComponent::update(const sf::Time &)
{
    view.setCenter(transform->position);
}

void CameraComponent::fixed_update(const sf::Time &)
{}

void CameraComponent::render(RenderingManager&)
{}

std::unique_ptr<Component> CameraComponent::clone(GameObject &newGameObject)
{
    return std::make_unique<CameraComponent>(newGameObject, dimensions);
}