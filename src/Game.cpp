#include "Game.h"

Game::Game()
{

}

void Game::runGame()
{
    sf::Clock timer;
    while (m_window.isOpen() && !m_states.empty())
    {
        auto& state = getCurrentState();

        m_window.clear();

        m_window.display();
        tryPop();
        handleEvents(); //done last so that window closing does not cause crash
    }
}

const sf::RenderWindow& Game::getWindow() const
{
    return m_window;
}

void Game::popState()
{
    m_shouldPopState = true;
}

GameState& Game::getCurrentState()
{
    return *m_states.back();
}

void Game::tryPop()
{
    if (m_shouldPopState)
    {
        if (m_states.empty())
            return;

        m_shouldPopState = false;
        m_states.pop_back();
    }
}

void Game::handleEvents()
{
    auto& state = getCurrentState();
    sf::Event event;

    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;

            default:
                break;
        }
    }
}

