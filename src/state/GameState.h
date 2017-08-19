#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include <SFML/Graphics.hpp>

class Game;

class GameState
{
    public:
        GameState(Game& game)
        :   m_pGame (&game){}

        virtual void handleEvents(sf::Event e)              = 0;
        virtual void handleInput ()                         = 0;

        virtual void update     (const sf::Time& deltaTime) = 0;
        virtual void fixedUpdate(const sf::Time& deltaTime) = 0;

        virtual void render(sf::RenderTarget& renderTarget) = 0;

    protected:
        Game* m_pGame;
};

#endif // GAMESTATE_H_INCLUDED
