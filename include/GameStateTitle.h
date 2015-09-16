#ifndef GAME_STATE_TITLE_H
#define GAME_STATE_TITLE_H

#include "IGameState.h"
#include "Gui.h"
#include "Button.h"
#include "Bot.h"
#include "Sound.h"
#include "Mute.h"

#include <SFML/Audio.hpp>

namespace av {
    class Game;

    class GameStateTitle: public IGameState {
    public:
        GameStateTitle(Game& game, bool mute);
        ~GameStateTitle();
        void draw(const double dt);
        void update();
        void handleInput();
    private:
        sf::Sprite m_background, m_decoration, m_title, m_overlay;
        Gui m_gui;
        Bot m_bot;
        Sound m_music;
        Mute* m_mute;
    };
}

#endif