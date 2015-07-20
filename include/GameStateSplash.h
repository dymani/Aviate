#ifndef GAME_STATE_SPLASH_H
#define GAME_STATE_SPLASH_H

#include <iostream>

#include "IGameState.h"

namespace av {
    class Game;

    class GameStateSplash: public IGameState {
    public:
        GameStateSplash(Game& game);
        void draw(const double dt);
        void update();
        void handleInput();
    private:
        sf::Sprite m_splash;
        int m_brightness;
        enum State {
            START, PAUSE, END
        } m_state;
        int m_splashNo, m_splashPauseCount;
    };
}

#endif