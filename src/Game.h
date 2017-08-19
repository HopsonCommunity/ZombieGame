#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class GameState{};

class Game
{
    public:
        Game();

        void runGame();

        const sf::RenderWindow& getWindow() const;

        template<typename T, typename... Args>
        void pushState(Args&&... args);

        void popState();

    private:
        GameState& getCurrentState();
        void tryPop();
        void handleEvents();

        sf::RenderWindow m_window;
        std::vector<std::unique_ptr<GameState>> m_states;
        bool m_shouldPopState = false;

};

template<typename T, typename... Args>
void Game::pushState(Args&&... args)
{
    m_states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
}

#endif // GAME_H_INCLUDED
