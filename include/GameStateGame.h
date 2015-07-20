#ifndef GAME_STATE_GAME_H
#define GAME_STATE_GAME_H

#include "IGameState.h"
#include "Player.h"

namespace av {
    class Game;

    class GameStateTitle: public IGameState {
    public:
        GameStateTitle(Game& game);
        void draw(const double dt);
        void update();
        void handleInput();
    private:
        sf::Sprite m_background, m_overlay;
    };
}

#endif