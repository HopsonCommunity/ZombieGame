#include <json.hpp>

#include "GameObjectFactory.h"
#include "../util/FileUtil.h"
#include "components/TestComponent.h"
#include "../Game.h"

namespace GameObject {
    GameObjectFactory::GameObjectFactory(GameState::Game& game) : m_last_ID(0), m_game(game) {}

    std::unique_ptr<GameObject> GameObjectFactory::createGameObject(std::string name) {
        if (templates.find(name) == templates.end())
            createTemplate(name);
        return templates.find(name)->second->clone(m_game.getCurrentState(), ++m_last_ID);
    }

    void GameObjectFactory::createTemplate(std::string name) {
        std::string source = Util::getFileContents("res/gameobjects/" + name);
        nlohmann::json json = nlohmann::json::parse(source.c_str());

        std::unique_ptr<GameObject> gameObject = std::make_unique<GameObject>(m_game.getCurrentState(), 0);

        std::vector<nlohmann::json> componentsJSON = json["components"];
        for (unsigned int i = 0; i < componentsJSON.size(); i++) {
            nlohmann::json componentJSON = componentsJSON[i];

            if (componentJSON["componentType"].get<std::string>() == "Test")
                gameObject->addComponent<TestComponent>(std::make_unique<TestComponent>(*gameObject, componentJSON));
        }

        templates[name] = std::move(gameObject);
    }
}