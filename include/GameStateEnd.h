#ifndef GAME_STATE_END_H
#define GAME_STATE_END_H

#include <fstream>
#include <SFML/Graphics.hpp>
#include "IGameState.h"
#include "Gui.h"
#include "Button.h"
#include "Sound.h"
#include "Mute.h"
#include "Buff.h"
#include "Score.h"

namespace av {
    class Game;

    class GameStateEnd: public IGameState {
    public:
        GameStateEnd(Game& game, std::vector<Buff*>& buffs, sf::Vector2f player, int bp, bool mute);
        ~GameStateEnd();
        void update();
        void draw(const double dt);
        void handleInput();
    private:
        Game& m_game;
        sf::Sprite m_background, m_decoration, m_overlay, m_end, m_player;
        Gui m_gui;
        Sound m_music;
        Mute* m_mute;
        std::vector<Buff*>& m_buffs;
        Score m_score;
        std::ifstream m_fin;
        std::ofstream m_fout;
    };
}

#endif