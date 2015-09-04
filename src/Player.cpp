#include "Player.h"
#include "Game.h"

namespace av {
    Player::Player(Game& game):m_game(game) {
        m_coord = {32, 0};
        m_state = IDLE;
        m_velocity = {0, 0};
        m_speedX = m_speedY = 0;
        GRAVITY = 0.2F;
        m_facingLeft = true;
        m_sprite.setTexture(game.getTexture("sprite"));
        m_sprite.setScale({6.0F, 6.0F});
        m_sprite.setTextureRect({9, 0, 9, 9});
        m_sprite.setPosition(float(m_coord.x - 4.5) * 6, float(82 * 6));
        m_spaceState = false;
    }

    void Player::update() {
        sf::Vector2f coord = m_coord;
        int mouseX = int(sf::Mouse::getPosition(m_game.getWindow()).x / 6);
        if(mouseX > coord.x) {
            m_facingLeft = false;
            m_speedX = 10.0F * (mouseX - coord.x) / 64;
            m_velocity.x += 0.5F;
            m_velocity.x = m_velocity.x > m_speedX?m_speedX:m_velocity.x;
        } else if(mouseX < coord.x) {
            m_facingLeft = true;
            m_speedX = -10.0F * (coord.x - mouseX) / 64;
            m_velocity.x -= 0.5F;
            m_velocity.x = m_velocity.x < m_speedX?m_speedX:m_velocity.x;
        }
        coord.x += m_velocity.x;
        switch(m_state) {
            case IDLE:
                break;
            case FALLING:
                m_speedY -= GRAVITY;
                m_speedY = m_speedY > 20?20:m_speedY;
            case FLYING:
                m_velocity.y = sqrt(150.0F - m_velocity.x * m_velocity.x) * m_speedY / 10;
                if(coord.y + m_velocity.y > 0) {
                    coord.y += m_velocity.y;
                } else {
                    coord.y = 0;
                    m_speedY = 0;
                    m_velocity.y = 0;
                    m_state = IDLE;
                }
                break;
        }
        if(coord.x <= 0) {
            coord.x = 0;
        } else if(coord.x >= 64) {
            coord.x = 64;
        }
        m_coord = coord;
    }

    void Player::handleInput(sf::Event& windowEvent) {
        if(windowEvent.type == sf::Event::KeyPressed && windowEvent.key.code == sf::Keyboard::Return)
            m_coord = {32, 0};
        if(windowEvent.type == sf::Event::KeyPressed) {
            if(windowEvent.key.code == sf::Keyboard::Space) {
                m_spaceState = true;
            }
        } else if(windowEvent.type == sf::Event::KeyReleased) {
            if(windowEvent.key.code == sf::Keyboard::Space) {
                m_spaceState = false;
            }
        }
        if(m_spaceState) {
            if(m_state != FLYING) {
                m_state = FLYING;
                m_speedY = 1.0F;
            }
        } else {
            if(m_state == FLYING) m_state = FALLING;
        }
    }

    void Player::draw() {
        if(m_facingLeft)
            m_sprite.setTextureRect({9, 0, 9, 9});
        else
            m_sprite.setTextureRect({9, 9, 9, 9});
        m_sprite.setPosition(float(m_coord.x - 4.5) * 6, float((82 - m_coord.y) * 6));
        m_game.getWindow().draw(m_sprite);
    }

    sf::Vector2f Player::getCoord() {
        return m_coord;
    }
}