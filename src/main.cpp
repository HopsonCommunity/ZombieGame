#include "Game.h"

#include "gameobject/GameObject.h"
#include "gameobject/components/TestComponent.h"

#include <memory>

int main()
{
    GameState::Game game;
    game.runGame();

    return 0;
}
