#include "MouseComponent.h"
#include "../../state/GameState.h"
#include "../../Game.h"
unsigned  MouseComponent::ID = 4;

MouseComponent::MouseComponent(GameObject &owner, nlohmann::json json)
        : Component(owner)
{

}

MouseComponent::MouseComponent(GameObject &owner)
        : Component(owner)
{

}

void MouseComponent::setup()
{
    transform = m_owner.getComponent<TransformComponent>();
    m_owner.getOwningState().getGamePointer()->getRenderWindow().setMouseCursorVisible(false);
}

void MouseComponent::update(const sf::Time &deltaTime)
{
    if (cameraComponent!= nullptr && cameraTransform != nullptr)
    {
        transform->position = sf::Vector2f(
                sf::Mouse::getPosition(m_owner.getOwningState().getGamePointer()->getRenderWindow()).x +
                cameraTransform->position.x - cameraComponent->view.getSize().x / 2,
                sf::Mouse::getPosition(m_owner.getOwningState().getGamePointer()->getRenderWindow()).y +
                cameraTransform->position.y - cameraComponent->view.getSize().y / 2);
    }
    else
        transform->position = sf::Vector2f(sf::Mouse::getPosition(m_owner.getOwningState().getGamePointer()->getRenderWindow()).x, sf::Mouse::getPosition(m_owner.getOwningState().getGamePointer()->getRenderWindow()).y);

}

void MouseComponent::fixed_update(const sf::Time &deltaTime)
{

}

void MouseComponent::render(sf::RenderTarget &renderTarget)
{
}

std::unique_ptr<Component> MouseComponent::clone(GameObject &newGameObject)
{
    return std::make_unique<MouseComponent>(newGameObject);
}
