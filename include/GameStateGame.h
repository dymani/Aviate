#ifndef GAME_STATE_GAME_H
#define GAME_STATE_GAME_H

#include "IGameState.h"
#include "Player.h"
#include "Gui.h"
#include "Button.h"
#include "Sound.h"
#include "Mute.h"

namespace av {
    class Game;

    class GameStateGame: public IGameState {
    public:
        GameStateGame(Game& game);
        ~GameStateGame();
        void draw(const double dt);
        void update();
        void handleInput();
    private:
        sf::Sprite m_background, m_decoration, m_overlay;
        Gui m_gui;
        Player m_player;
        Sound m_music;
        Mute* m_mute;
        sf::View m_view;
        bool m_pauseState;
        sf::RectangleShape m_dim;
    };
}

#endif