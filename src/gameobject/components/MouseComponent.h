#include <json.hpp>
#include "Component.h"
#include "../GameObject.h"
#include "TransformComponent.h"
#include "CameraComponent.h"

class MouseComponent : public Component
{
public:
    MouseComponent(GameObject& owner, nlohmann::json json);
    MouseComponent(GameObject& owner);

    void setup() override;
    void update(const sf::Time& deltaTime) override;
    void fixed_update(const sf::Time &deltaTime) override;
    void render(sf::RenderTarget& renderTarget) override;
    std::unique_ptr<Component> clone(GameObject& newGameObject) override;

    TransformComponent* transform;
    TransformComponent* cameraTransform;
    CameraComponent* cameraComponent;

    static unsigned ID;
};