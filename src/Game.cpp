#include "Game.h"

#include "state/PlayingState.h"
#include "util/Renderer.h"
#include "util/RenderingManager.h"

Game::Game()
:   m_window    ({1280, 720}, "Zombie Game"),
    m_factory   (*this)
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
        RenderingManager renderingManager(new Renderer(m_window));
        state.render(renderingManager);
        renderingManager.render();
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

template<typename T, typename... Args>
void Game::pushState(Args&&... args)
{
    m_states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    m_states.back()->setup();
}


void Game::popState()
{
    m_shouldPopState = true;
}

GameState& Game::getCurrentState()
{
    return *m_states.back();
}

GameObjectFactory& Game::getGameObjectFactory()
{
    return m_factory;
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

sf::RenderWindow& Game::getRenderWindow()
{
    return m_window;
}


