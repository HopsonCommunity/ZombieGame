#include "RendererComponent.h"
#include "../GameObject.h"
#include "../../resource/ResourceHolder.h"

unsigned  RendererComponent::ID = 1;

RendererComponent::RendererComponent(GameObject &owner, nlohmann::json json) : Component(owner)
{
    textureName = json["texture"];
    sprite = sf::Sprite(ResourceHolder::get().textures.get(textureName));
    offset_position = sf::Vector2f(json["offset_position"][0], json["offset_position"][1]);
    offset_rotation = json["offset_rotation"];
    scale = sf::Vector2f(json["scale"][0], json["scale"][1]);
    zIndex = static_cast<ZIndex_t>(json["zIndex"]);
}
RendererComponent::RendererComponent(GameObject &owner, std::string textureName, sf::Vector2f offset_position,
                                     double offset_rotation, sf::Vector2f scale, ZIndex_t zIndex)
        : Component(owner)
        , offset_position(offset_position)
        , offset_rotation(offset_rotation)
        , scale(scale)
        , zIndex(zIndex)
{
    sprite = sf::Sprite(ResourceHolder::get().textures.get(textureName));
}

void RendererComponent::setup()
{
    transform = m_owner.getComponent<TransformComponent>();
}

void RendererComponent::update(const sf::Time &)
{}

void RendererComponent::fixed_update(const sf::Time &)
{}

void RendererComponent::render(Renderer& renderTarget)
{
    sprite.setOrigin(offset_position);
    sprite.setPosition(transform->position);
    sprite.setRotation(transform->rotation + offset_rotation);
    sprite.setScale(scale);
    renderTarget.draw(sprite, zIndex);
}

std::unique_ptr<Component> RendererComponent::clone(GameObject& newGameObject)
{
    return std::make_unique<RendererComponent>(newGameObject, textureName, offset_position, offset_rotation, scale, zIndex);
}
