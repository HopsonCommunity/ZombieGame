#include "PlayingState.h"
#include "../gameobject/components/TransformComponent.h"
#include "../gameobject/components/TestComponent.h"
#include "../gameobject/components/PlayerComponent.h"
#include "../gameobject/components/CameraComponent.h"
#include "../gameobject/components/MouseComponent.h"
#include "../gameobject/components/FPSComponent.h"
#include "../gameobject/components/CameraComponent.h"

PlayingState::PlayingState(Game& game)
:   GameState   (game)
{

}


void PlayingState::handleEvents(sf::Event)
{

}

void PlayingState::handleInput()
{

}

void PlayingState::update(const sf::Time& deltaTime)
{
    for (size_t i=0; i<m_gameObjects.size(); ++i){
        m_gameObjects[i]->update(deltaTime);
    }
    m_ColliderSpace.update(deltaTime);
}

void PlayingState::fixedUpdate(const sf::Time& deltaTime)
{
    for (size_t i=0; i<m_gameObjects.size(); ++i){
        m_gameObjects[i]->fixed_update(deltaTime);
    }
}

void PlayingState::render(Renderer& renderTarget)
{
    renderTarget.setView(cameraComponent->view);
    for (size_t i=0; i<m_gameObjects.size(); ++i){
        m_gameObjects[i]->render(renderTarget);
    }
    m_debugRenderer.draw(renderTarget);
}

void PlayingState::setup()
{
    constexpr int RANGE = 25;
    for (int x = -RANGE; x <= RANGE; ++x)
    {
        for (int y = -RANGE; y <= RANGE; ++y)
        {
            m_gameObjects.push_back(m_pGame->getGameObjectFactory().createGameObject("grass"));
            auto ground = m_gameObjects.back();
            ground->getComponent<TransformComponent>()->position = sf::Vector2f(x * 80, y * 80);
        }
    }
    m_gameObjects.push_back(m_pGame->getGameObjectFactory().createGameObject("mouse"));
    m_mouse = m_gameObjects.back();
    m_gameObjects.push_back(m_pGame->getGameObjectFactory().createGameObject("player"));
    m_player = m_gameObjects.back();
    m_gameObjects.push_back(m_pGame->getGameObjectFactory().createGameObject("bd"));
    m_building = m_gameObjects.back();
    m_gameObjects.push_back(m_pGame->getGameObjectFactory().createGameObject("fps"));
    m_fps = m_gameObjects.back();

    m_player->getComponent<PlayerComponent>()->mouse = m_mouse->getComponent<TransformComponent>();
    cameraComponent = m_player->getComponent<CameraComponent>();
    m_mouse->getComponent<MouseComponent>()->cameraTransform = m_player->getComponent<TransformComponent>();
    m_mouse->getComponent<MouseComponent>()->cameraComponent = cameraComponent;
    m_fps->getComponent<FPSComponent>()->camera = cameraComponent;

}
