#include "Game.h"

#include "state/PlayingState.h"

Game::Game()
:   m_window    ({1280, 720}, "Zombie Game")
{
    pushState<PlayingState>(*this);
}

void Game::runGame()
{
    unsigned tickCount = 0;
    constexpr unsigned  UPDATES_PER_FRAME = 30;
    const sf::Time      MS_PER_UPDATE       = sf::seconds(1.0f / float(UPDATES_PER_FRAME));

    sf::Clock timer;
    sf::Time  lastTime = timer.getElapsedTime();
    sf::Time  lag      = sf::Time::Zero;

    while (m_window.isOpen() && !m_states.empty())
    {
        auto& state = getCurrentState();

        //Time handling for the fixed update and
        //getting delta-time
        auto time      = timer.getElapsedTime();
        auto elapsed   = time - lastTime;

        lastTime = time;
        lag     += elapsed;

        //Real time updates
        state.handleInput();
        state.update(elapsed);

        //Fixed update
        while (lag > MS_PER_UPDATE)
        {
            tickCount++;
            lag -= MS_PER_UPDATE;
            state.fixedUpdate(elapsed);
        }

        //Render
        m_window.clear();
        state.render(m_window);
        m_window.display();

        //done last so that window closing/ state pointer dangling does not cause crash
        handleEvents();
        tryPop();
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
    sf::Event event;

    while (m_window.pollEvent(event))
    {
        getCurrentState().handleEvents(event);
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

