#include <json.hpp>

#include "GameObjectFactory.h"
#include "../util/FileUtil.h"
#include "components/TestComponent.h"
#include "../Game.h"

GameObjectFactory::GameObjectFactory(Game& game)
: m_last_ID(0)
, m_game(game)
{}

std::unique_ptr<GameObject> GameObjectFactory::createGameObject(std::string name)
{
    if (templates.find(name) == templates.end())
        createTemplate(name);
    return templates.find(name)->second->clone(m_game.getCurrentState(), ++m_last_ID);
}

void GameObjectFactory::createTemplate(std::string name)
{
    auto source         = getFileContents("res/gameobjects/" + name);
    auto json           = nlohmann::json::parse(source.c_str());
    auto gameObject     = std::make_unique<GameObject>(m_game.getCurrentState(), 0);
    auto componentsJSON = json["components"];

    for (unsigned i = 0; i < componentsJSON.size(); i++)
    {
        auto componentJSON = componentsJSON[i];

        if (componentJSON["componentType"].get<std::string>() == "Test")
            gameObject->addComponent<TestComponent>(std::make_unique<TestComponent>(*gameObject, componentJSON));
    }

    templates[name] = std::move(gameObject);
}
