#pragma once

#include "GameObject.h"

class Game;

class GameObjectFactory
{
    public:
        GameObjectFactory(Game& game);
        std::unique_ptr<GameObject> createGameObject(const std::string& name);

    private:
        void createTemplate(const std::string& name);

        std::unordered_map<std::string, std::unique_ptr<GameObject>> templates;
        unsigned  m_last_ID;
        Game& m_game;
};

