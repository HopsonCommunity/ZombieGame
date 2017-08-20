#pragma once

#include "GameObject.h"

namespace GameState {
    class Game;
}

namespace GameObject {

    class GameObjectFactory {
    public:
        GameObjectFactory(GameState::Game& game);
        std::unique_ptr<GameObject> createGameObject(std::string name);
    private:
        void createTemplate(std::string name);
        std::unordered_map<std::string, std::unique_ptr<GameObject>> templates;
        unsigned int m_last_ID;
        GameState::Game& m_game;
    };

}
