#include "FPSComponent.h"

#include "CameraComponent.h"

#include "../GameObject.h"
#include "../../resource/ResourceHolder.h"

unsigned int FPSComponent::ID = 9;

FPSComponent::FPSComponent(GameObject& owner, nlohmann::json json)
:   Component(owner)
,   prev_fps{0}
{
    text = sf::Text("0", ResourceHolder::get().fonts.get(json["font"]), json["size"]);
    position = sf::Vector2f((static_cast<int>(json["position"][0]) - 50) / 100.f, (static_cast<int>(json["position"][1]) - 50) / 100.f);
    text.setFillColor(sf::Color::White);
}

FPSComponent::FPSComponent(GameObject& owner, sf::Text const& text, sf::Vector2f const& position)
:   Component(owner)
,   text(text)
,   position(position)
,   prev_fps{0} {}

void FPSComponent::setup() 
{}

void FPSComponent::update(const sf::Time& dt)
{
    if (dt.asMicroseconds() != 0) {
        for (int i = 0; i < AVERAGE_FPS_COUNT - 1; ++i)
            prev_fps[i] = prev_fps[i+1];
        prev_fps[AVERAGE_FPS_COUNT - 1] = static_cast<int>((1.f/dt.asMicroseconds()) * 1000000);
        int fps = 0;
        for (int i = 0; i < AVERAGE_FPS_COUNT; ++i) fps += prev_fps[i];
        text.setString(std::to_string(fps / AVERAGE_FPS_COUNT));
        text.setOrigin(text.getLocalBounds().width/2.0f,text.getLocalBounds().height/2.0f);
        text.setPosition( 
            camera->transform->position.x - position.x * camera->view.getSize().x,
            camera->transform->position.y - position.y * camera->view.getSize().y
        );
    }
}

void FPSComponent::fixed_update(const sf::Time&)
{}

void FPSComponent::render(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(text);
}

std::unique_ptr<Component> FPSComponent::clone(GameObject& newGameObject)
{
    return std::make_unique<FPSComponent>(newGameObject, text, position);
}