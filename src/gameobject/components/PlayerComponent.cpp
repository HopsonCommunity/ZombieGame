#include "PlayerComponent.h"
#include "../GameObject.h"

unsigned PlayerComponent::ID = 3;

PlayerComponent::PlayerComponent(GameObject &owner, nlohmann::json json)
        : Component(owner)
{
    speed = json["speed"];
}

PlayerComponent::PlayerComponent(GameObject &owner, float speed)
        : Component(owner), speed(speed)
{}

void PlayerComponent::setup()
{
    transform = m_owner.getComponent<TransformComponent>();
}

void PlayerComponent::update(const sf::Time &deltaTime)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        transform->position.y -= deltaTime.asMicroseconds() / 10000.0 * speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        transform->position.y += deltaTime.asMicroseconds() / 10000.0 * speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        transform->position.x += deltaTime.asMicroseconds() / 10000.0 * speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        transform->position.x -= deltaTime.asMicroseconds() / 10000.0 * speed;
    }

    if(mouse != nullptr) {
        transform->lookAt(mouse);
    }
}

void PlayerComponent::fixed_update(const sf::Time &)
{}

void PlayerComponent::render(Renderer &)
{}

std::unique_ptr<Component> PlayerComponent::clone(GameObject &newGameObject)
{
    return std::make_unique<PlayerComponent>(newGameObject, speed);
}

