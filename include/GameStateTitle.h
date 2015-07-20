#ifndef GAME_STATE_TITLE_H
#define GAME_STATE_TITLE_H

#include "IGameState.h"
#include "Gui.h"
#include "Button.h"

namespace av {
    class Game;

    class GameStateTitle: public IGameState {
    public:
        GameStateTitle(Game& game);
        void draw(const double dt);
        void update();
        void handleInput();
    private:
        sf::Sprite m_background, m_overlay, m_title;
        Gui m_gui;
    };
}

#endif