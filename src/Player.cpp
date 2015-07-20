#include "Player.h"
#include "Game.h"

namespace av {
    Player::Player(Game& game):m_game(game) {
        m_coord = m_newCoord = {32, 0};
        m_facingLeft = true;
        m_moving = false;
        m_flying = false;
        m_sprite.setTexture(game.getTexture("sprite"));
        m_sprite.setTextureRect({0, 0, 9, 9});
        m_sprite.setScale({6.0F, 6.0F});
        m_sprite.setPosition(float(m_coord.x - 4.5) * 6, float(82 * 6));
    }

    void Player::update() {

    }

    void Player::handleInput(sf::Event& windowEvent) {

    }

    void Player::draw() {
        m_game.getWindow().draw(m_sprite);
    }
}