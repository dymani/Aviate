#include "Level.h"
#include "Game.h"
#include "Player.h"

namespace av {
    Level::Level(Game& game, Player& player):m_game(game), m_player(player) {
        m_sprite.setTexture(m_game.getTexture("gui"));
        m_sprite.setTextureRect({0, 66, 15, 10});
        m_sprite.setScale(6.0F, 6.0F);
        m_sprite.setPosition(6.0F, 510.0F);
        m_digit.setTexture(m_game.getTexture("gui"));
        m_digit.setTextureRect({6, 80, 4, 6});
        m_digit.setScale(6.0F, 6.0F);
        m_digit.setPosition(66.0F, 522.0F);
        m_level = 1;
    }

    void Level::update() {
        m_level = m_player.getLevel();
    }

    void Level::draw() {
        m_game.getWindow().draw(m_sprite);
        if(m_level < 10) {
            m_digit.setTextureRect({1 + 5 * m_level, 80, 4, 6});
            m_digit.setPosition(66.0F, 522.0F);
            m_game.getWindow().draw(m_digit);
        } else {
            m_digit.setTextureRect({6 , 80, 4, 6});
            m_digit.setPosition(36.0F, 522.0F);
            m_game.getWindow().draw(m_digit);
            m_digit.setTextureRect({1 , 80, 4, 6});
            m_digit.setPosition(66.0F, 522.0F);
            m_game.getWindow().draw(m_digit);
        }
    }
}