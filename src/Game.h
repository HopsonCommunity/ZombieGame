#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "state/GameState.h"
#include "gameobject/GameObjectFactory.h"

class Game
{
    public:
        Game();

        void runGame();

        const sf::RenderWindow& getWindow() const;

        template<typename T, typename... Args>
        void pushState(Args&&... args);

        void popState();

        GameState& getCurrentState();

    private:
        void tryPop();
        void handleEvents();

        sf::RenderWindow m_window;
        std::vector<std::unique_ptr<GameState>> m_states;
        bool m_shouldPopState = false;
        GameObjectFactory m_factory;

};

template<typename T, typename... Args>
void Game::pushState(Args&&... args)
{
    m_states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
}
