#include "AnimationComponent.h"

#include "TransformComponent.h"

#include "../GameObject.h"

#include "../../resource/ResourceHolder.h"

unsigned AnimationComponent::ID = 6;

AnimationComponent::AnimationComponent(GameObject& owner, nlohmann::json json)
        : Component(owner)
{
    FrameTime = 1000.f/float(json["FPS"]);
    CurrentFrameID = json["startFrame"];

    textureName = json["texture"];
    sprite = sf::Sprite(ResourceHolder::get().textures.get(textureName));
    offset_position = sf::Vector2f(json["offset_position"][0], json["offset_position"][1]);
    offset_rotation = json["offset_rotation"];
    frame_width = json["frame_width"];
    scale = sf::Vector2f(json["scale"][0], json["scale"][1]);
    zIndex = json["zIndex"];
}

AnimationComponent::AnimationComponent(GameObject& owner, float framesPerSecond, int currentFrameID,
                                       std::string textureName, sf::Vector2f offset_position, double offset_rotation,
                                       sf::Vector2f scale, int frame_width, int zIndex)
        : Component(owner)
        , FrameTime(framesPerSecond/1000.f)
        , CurrentFrameID(currentFrameID)
        , offset_position(offset_position), offset_rotation(offset_rotation), scale(scale)
        , frame_width(frame_width)
        , zIndex(zIndex)
{
    sprite = sf::Sprite(ResourceHolder::get().textures.get(textureName));
}

void AnimationComponent::setup()
{
    CurrentFrameID=0;
    transform = m_owner.getComponent<TransformComponent>();
    rectSourceSprite.height=sprite.getTextureRect().height;
    rectSourceSprite.width=frame_width;
    rectSourceSprite.top=0;
    clock.restart();
    MaxFrameID=sprite.getTextureRect().width/frame_width;
    frame_direction=1;
}

void AnimationComponent::update(const sf::Time& )
{
    if (clock.getElapsedTime().asMilliseconds()>=FrameTime){
        CurrentFrameID+=frame_direction;
        if (CurrentFrameID>=MaxFrameID){
            frame_direction=-1;
            CurrentFrameID=MaxFrameID-1;
        }else if (CurrentFrameID<=0){
            frame_direction=1;
            CurrentFrameID=0;
        }
        clock.restart();
    }
}

void AnimationComponent::fixed_update(const sf::Time &)
{

}

void AnimationComponent::render(Renderer& renderTarget)
{
    rectSourceSprite.left=frame_width*CurrentFrameID;
    sprite.setTextureRect(rectSourceSprite);
    sprite.setOrigin(offset_position);
    sprite.setPosition(transform->position);
    sprite.setRotation(transform->rotation + offset_rotation);
    sprite.setScale(scale);
    renderTarget.draw({zIndex, [&](Renderer& renderer){
        renderer.draw(sprite);
    }});
}

std::unique_ptr<Component> AnimationComponent::clone(GameObject& newGameObject)
{
    return std::make_unique<AnimationComponent>(newGameObject, FrameTime*1000.f, CurrentFrameID,
                                                textureName, offset_position, offset_rotation, scale, frame_width, zIndex);
}

