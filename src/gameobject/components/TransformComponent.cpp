#include "TransformComponent.h"
#include "../../util/Mathf.h"

unsigned TransformComponent::ID = 2;

TransformComponent::TransformComponent(GameObject &owner, sf::Vector2f position, float rotation, bool renderTransform)
        : Component(owner), position(position), rotation(rotation), renderTransform(renderTransform)
{

}

TransformComponent::TransformComponent(GameObject &owner, nlohmann::json json)
        : Component(owner)
{
    position = sf::Vector2f(json["position"][0], json["position"][1]);
    rotation = json["rotation"];
    renderTransform = json["renderTransform"];
}

void TransformComponent::setup()
{

}

void TransformComponent::update(const sf::Time& deltaTime)
{

}

void TransformComponent::fixed_update(const sf::Time &deltaTime)
{

}

void TransformComponent::render(sf::RenderTarget& renderTarget)
{
    if (renderTransform)
    {
        sf::CircleShape circle = sf::CircleShape(6);
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        circle.setPosition(position.x, position.y);
        circle.setFillColor(sf::Color::White);
        renderTarget.draw(circle);

        sf::CircleShape rotationIndicator = sf::CircleShape(2);
        rotationIndicator.setOrigin(rotationIndicator.getRadius(), rotationIndicator.getRadius());
		rotationIndicator.setPosition(cos(math::radians(rotation)) * 10 + position.x, sin(math::radians(rotation)) * 10 + position.y);
        rotationIndicator.setFillColor(sf::Color::Red);
        renderTarget.draw(rotationIndicator);
    }
}

void TransformComponent::lookAt(TransformComponent* target)
{
    rotation = math::degrees(atan2((target->position.y - position.y), (target->position.x - position.x)));
}

std::unique_ptr<Component> TransformComponent::clone(GameObject& newGameObject)
{
    return std::make_unique<TransformComponent>(newGameObject, position, rotation, renderTransform);
}
