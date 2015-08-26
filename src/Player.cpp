#include "Player.h"
#include "Game.h"

namespace av {
    Player::Player(Game& game):m_game(game) {
        m_coord = m_newCoord = {32, 0};
        m_facingLeft = true;
        m_moving = false;
        m_flying = false;
        m_sprite.setTexture(game.getTexture("sprite"));
        m_sprite.setScale({6.0F, 6.0F});
        m_sprite.setTextureRect({9, 0, 9, 9});
        m_sprite.setPosition(float(m_coord.x - 4.5) * 6, float(82 * 6));
    }

    void Player::update() {
        m_newCoord.x = float(sf::Mouse::getPosition(m_game.getWindow()).x / 6);
        if(m_newCoord.x > m_coord.x) {
            m_facingLeft = false;
        } else if(m_newCoord.x < m_coord.x) {
            m_facingLeft = true;
        } else {

        }
        if(m_newCoord.x <= 0) {
            m_newCoord.x = 0;
        } else if(m_newCoord.x >= 64) {
            m_newCoord.x = 64;
        }
        m_coord = m_newCoord;
    }

    void Player::handleInput(sf::Event& windowEvent) {

    }

    void Player::draw() {
        if(m_facingLeft)
            m_sprite.setTextureRect({9, 0, 9, 9});
        else
            m_sprite.setTextureRect({9, 9, 9, 9});
        m_sprite.setPosition(float(m_coord.x - 4.5) * 6, float(82 * 6));
        m_game.getWindow().draw(m_sprite);
    }
}