#ifndef I_GAME_STATE_H
#define I_GAME_STATE_H

#include "Game.h"

namespace av {
    class IGameState {
    public:
        IGameState(Game& game):m_game(game) {
        }
        virtual void draw(const double dt) = 0;
        virtual void update() = 0;
        virtual void handleInput() = 0;
    protected:
        Game& m_game;
    };
}

#endif