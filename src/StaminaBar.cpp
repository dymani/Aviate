#include "StaminaBar.h"
#include "Game.h"
#include "Player.h"

namespace av {
    StaminaBar::StaminaBar(Game& game, Player& player): m_game(game), m_player(player) {
        m_base.setTexture(game.getTexture("gui"));
        m_base.setTextureRect({11, 48, 51, 14});
        m_base.setPosition(66, 0);
        m_base.setScale(6, 6);
        m_bar.setTexture(game.getTexture("gui"));
        m_bar.setTextureRect({11, 63, 44, 2});
        m_bar.setPosition(66, 48);
        m_bar.setScale(6, 6);
        m_top.setTexture(game.getTexture("gui"));
        m_top.setTextureRect({0, 48, 11, 14});
        m_top.setPosition(0, 0);
        m_top.setScale(6, 6);
        m_cover.setTexture(game.getTexture("gui"));
        m_cover.setScale(6, 6);
        m_hp = 44;
    }

    bool StaminaBar::update() {
        m_stamina = int(m_player.getStamina() / 100);
        if(m_end) {
            m_hp -= 2;
            m_cover.setTextureRect({10, 56, 44 - m_hp, 3});
            m_cover.setPosition(66 + float(m_hp * 6), 30);
            if(m_hp <= 0)
                return true;
        }
        return false;
    }

    void StaminaBar::draw() {
        m_game.getWindow().draw(m_base);
        int length = int(44 * m_stamina / 100);
        m_bar.setTextureRect({(55 - length), 63, length, 2});
        m_game.getWindow().draw(m_bar);
        m_game.getWindow().draw(m_top);
        if(m_end) m_game.getWindow().draw(m_cover);
    }

    void StaminaBar::end() {
        m_end = true;
    }
}
