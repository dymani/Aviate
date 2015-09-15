#ifndef GAME_STATE_GAME_H
#define GAME_STATE_GAME_H

#include "IGameState.h"
#include "Player.h"
#include "Gui.h"
#include "Button.h"
#include "Sound.h"
#include "Mute.h"
#include "StaminaBar.h"
#include "Metre.h"
#include "Buff.h"
#include "BpCounter.h"
#include "Level.h"

namespace av {
    class Game;

    class GameStateGame: public IGameState {
    public:
        GameStateGame(Game& game);
        ~GameStateGame();
        void update();
        void draw(const double dt);
        void handleInput();
    private:
        sf::Sprite m_background, m_decoration, m_overlay;
        Gui m_gui;
        Player m_player;
        Sound m_music;
        Mute* m_mute;
        sf::View m_view;
        bool m_pauseState;
        bool m_end;
        sf::RectangleShape m_dim;
        StaminaBar m_stamina;
        Metre m_metre;
        std::vector<Buff*> m_buffs;
        BpCounter m_bpCounter;
        float m_viewVelocity, m_viewSpeed, m_viewCoord;
        Level m_level;
        int m_generated, m_lastBuff;
    };
}

#endif