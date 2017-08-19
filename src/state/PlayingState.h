#ifndef PLAYINGSTATE_H_INCLUDED
#define PLAYINGSTATE_H_INCLUDED

#include "GameState.h"

class PlayingState: public GameState
{
    public:
        PlayingState(Game& game);

        void handleEvents(sf::Event e)              override;
        void handleInput ()                         override;

        void update     (const sf::Time& deltaTime) override;
        void fixedUpdate(const sf::Time& deltaTime) override;

        void render(sf::RenderTarget& renderTarget) override;

    private:


};

#endif // PLAYINGSTATE_H_INCLUDED
