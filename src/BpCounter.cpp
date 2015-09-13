#include "BpCounter.h"
#include "Game.h"
#include "Player.h"

namespace av {
    BpCounter::BpCounter(Game& game, Player& player): m_game(game), m_player(player) {
        m_sprite.setTexture(m_game.getTexture("gui"));
        m_sprite.setTextureRect({16, 66, 20, 10});
        m_sprite.setPosition({264, 510});
        m_sprite.setScale(6.0F, 6.0F);
        m_digit.setTexture(m_game.getTexture("gui"));
        m_digit.setScale(6.0F, 6.0F);
    }

    void BpCounter::update() {
        m_bp = m_player.getBp();
    }

    void BpCounter::draw() {
        m_game.getWindow().draw(m_sprite);
        int u = m_bp % 10;
        int t = int(m_bp % 100 - u) / 10;
        int h = int((m_bp - t * 10 - u) / 100);
        if(h > 0) {
            m_digit.setTextureRect({1 + 5 * h, 80, 4, 6});
            m_digit.setPosition({270, 522});
            m_game.getWindow().draw(m_digit);
        }
        if(t > 0 || h > 0) {
            m_digit.setTextureRect({1 + 5 * t, 80, 4, 6});
            m_digit.setPosition({300, 522});
            m_game.getWindow().draw(m_digit);
        }
        m_digit.setTextureRect({1 + 5 * u, 80, 4, 6});
        m_digit.setPosition({330, 522});
        m_game.getWindow().draw(m_digit);
    }
}