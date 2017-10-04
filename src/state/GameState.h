#pragma once

#include <SFML/Graphics.hpp>
#include "../util/NonCopyable.h"
#include "../systems/ColliderSpace.h"

class Game;

class GameState : public NonCopyable
{
    public:
        GameState(Game& game)
        :   m_pGame (&game){}

        ~GameState() = default;

        virtual void handleEvents(sf::Event e)              = 0;
        virtual void handleInput ()                         = 0;

        virtual void update     (const sf::Time& deltaTime) = 0;
        virtual void fixedUpdate(const sf::Time& deltaTime) = 0;

        virtual void setup() = 0;

        virtual void render(sf::RenderTarget& renderTarget) = 0;

        Game* getGamePointer() { return m_pGame;}
        ColliderSpace* getColliderSpace() { return &m_ColliderSpace; }

    protected:
        Game* m_pGame;
        ColliderSpace m_ColliderSpace;
};

