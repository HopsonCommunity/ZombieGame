#pragma once

#include "GameState.h"
#include "../Game.h"
#include "../util/RenderingManager.h"

class CameraComponent;

class PlayingState: public GameState
{
    public:
        PlayingState(Game& game);

        void handleEvents(sf::Event e)              override;
        void handleInput ()                         override;

        void update     (const sf::Time& deltaTime) override;
        void fixedUpdate(const sf::Time& deltaTime) override;

        void render(RenderingManager& renderTarget)         override;

        void setup() override;

    private:

        std::vector<std::shared_ptr<GameObject>> m_gameObjects;

        std::shared_ptr<GameObject> m_player;
        std::shared_ptr<GameObject> m_mouse;
        std::shared_ptr<GameObject> m_building;
        std::shared_ptr<GameObject> m_fps;

        CameraComponent* cameraComponent;
    };

