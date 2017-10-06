#include <json.hpp>

#include "GameObjectFactory.h"
#include "../util/FileUtil.h"
#include "components/TestComponent.h"
#include "../Game.h"
#include "components/TransformComponent.h"
#include "components/RendererComponent.h"
#include "components/PlayerComponent.h"
#include "components/MouseComponent.h"
#include "components/CameraComponent.h"
#include "components/AnimationComponent.h"
#include "components/ColliderAABBComponent.h"
#include "components/RigidBodyComponent.h"

GameObjectFactory::GameObjectFactory(Game& game)
: m_last_ID(0)
, m_game(game)
{}

std::unique_ptr<GameObject> GameObjectFactory::createGameObject(const std::string& name)
{
    if (templates.find(name) == templates.end())
        createTemplate(name);
    return templates.find(name)->second->clone(m_game.getCurrentState(), ++m_last_ID);
}

void GameObjectFactory::createTemplate(const std::string& name)
{
    auto source         = getFileContents("res/gameobjects/" + name + ".json");
    auto json           = nlohmann::json::parse(source.c_str());
    auto gameObject     = std::make_unique<GameObject>(m_game.getCurrentState(), 0);
    auto componentsJSON = json["components"];

    for (unsigned i = 0; i < componentsJSON.size(); i++)
    {
        auto componentJSON = componentsJSON[i];

        if (componentJSON["componentType"].get<std::string>() == "Test")
            gameObject->addComponent<TestComponent>(std::make_unique<TestComponent>(*gameObject, componentJSON));
        if (componentJSON["componentType"].get<std::string>() == "Renderer")
            gameObject->addComponent<RendererComponent>(std::make_unique<RendererComponent>(*gameObject, componentJSON));
        if (componentJSON["componentType"].get<std::string>() == "Transform")
            gameObject->addComponent<TransformComponent>(std::make_unique<TransformComponent>(*gameObject, componentJSON));
        if (componentJSON["componentType"].get<std::string>() == "Player")
            gameObject->addComponent<PlayerComponent>(std::make_unique<PlayerComponent>(*gameObject, componentJSON));
        if (componentJSON["componentType"].get<std::string>() == "Mouse")
            gameObject->addComponent<MouseComponent>(std::make_unique<MouseComponent>(*gameObject, componentJSON));
        if (componentJSON["componentType"].get<std::string>() == "Camera")
            gameObject->addComponent<CameraComponent>(std::make_unique<CameraComponent>(*gameObject, componentJSON));
        if (componentJSON["componentType"].get<std::string>() == "Animation")
            gameObject->addComponent<AnimationComponent>(std::make_unique<AnimationComponent>(*gameObject, componentJSON));
        if (componentJSON["componentType"].get<std::string>() == "ColliderAABB")
            gameObject->addComponent<ColliderAABBComponent>(std::make_unique<ColliderAABBComponent>(*gameObject, componentJSON));
        if (componentJSON["componentType"].get<std::string>() == "RigidBody")
            gameObject->addComponent<RigidBodyComponent>(std::make_unique<RigidBodyComponent>(*gameObject, componentJSON));
    }

    templates[name] = std::move(gameObject);
}
