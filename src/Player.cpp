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
        m_frame = 1;
        m_interval = 0;
        m_stamina = 10000;
    }

    void Player::update() {
        sf::Vector2f coord = m_coord;
        int mouseX = int(sf::Mouse::getPosition(m_game.getWindow()).x / 6);
        if(mouseX > coord.x) {
            if(mouseX - coord.x > 0.1) {
                m_facingLeft = false;
                m_speedX = 10.0F * (mouseX - coord.x) / 64;
                m_velocity.x += 0.5F;
                m_velocity.x = m_velocity.x > m_speedX?m_speedX:m_velocity.x;
            }
        } else if(mouseX < coord.x) {
            if(coord.x - mouseX > 0.1) {
                m_facingLeft = true;
                m_speedX = -10.0F * (coord.x - mouseX) / 64;
                m_velocity.x -= 0.5F;
                m_velocity.x = m_velocity.x < m_speedX?m_speedX:m_velocity.x;
            }
        }
        coord.x += m_velocity.x;
        switch(m_state) {
            case IDLE:
                break;
            case FALLING:
                m_speedY -= GRAVITY;
                m_speedY = m_speedY < -10?-10:m_speedY;
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
                if(m_state == FLYING)
                    m_stamina -= int(m_velocity.y * 10);
                break;
        }
        if(coord.x <= 0) {
            coord.x = 0;
        } else if(coord.x >= 64) {
            coord.x = 64;
        }
        m_coord = coord;
        m_interval++;
    }

    void Player::handleInput(sf::Event& windowEvent) {
#if _DEBUG
        if(windowEvent.type == sf::Event::KeyPressed && windowEvent.key.code == sf::Keyboard::Return) {
            m_stamina = 10000;
        }
#endif
        if(windowEvent.type == sf::Event::KeyPressed) {
            if(windowEvent.key.code == sf::Keyboard::Space) {
                m_spaceState = true;
            }
        } else if(windowEvent.type == sf::Event::KeyReleased) {
            if(windowEvent.key.code == sf::Keyboard::Space) {
                m_spaceState = false;
            }
        }
        if(m_stamina > 0) {
            if(m_spaceState) {
                if(m_state != FLYING) {
                    m_state = FLYING;
                    m_speedY = 1.0F;
                }
            } else {
                if(m_state == FLYING) m_state = FALLING;
            }
        } else {
            if(m_state == FLYING)
                m_state = FALLING;
        }
    }

    void Player::draw() {
        if(m_facingLeft) {
            if(m_velocity.x > -0.2 && m_state == IDLE) {
                m_sprite.setTextureRect({9, 0, 9, 9});
            } else if(m_state == IDLE) {
                switch(m_frame) {
                    case 0:
                        m_sprite.setTextureRect({0, 0, 9, 9});
                        break;
                    case 1:
                        m_sprite.setTextureRect({9, 0, 9, 9});
                        break;
                    case 2:
                        m_sprite.setTextureRect({18, 0, 9, 9});
                        break;
                }
                if(m_interval >= 200) {
                    m_frame = m_frame == 2?0:m_frame + 1;
                }
            } else if(m_state == FLYING) {
                m_sprite.setTextureRect({27, 0, 9, 9});
            } else {
                m_sprite.setTextureRect({36, 9, 9, 9});
            }
        } else {
            if(m_velocity.x < 0.2 && m_state == IDLE) {
                m_sprite.setTextureRect({9, 9, 9, 9});
            } else if(m_state == IDLE) {
                switch(m_frame) {
                    case 0:
                        m_sprite.setTextureRect({0, 9, 9, 9});
                        break;
                    case 1:
                        m_sprite.setTextureRect({9, 9, 9, 9});
                        break;
                    case 2:
                        m_sprite.setTextureRect({18, 9, 9, 9});
                        break;
                }
                if(m_interval >= 200) {
                    m_frame = m_frame == 2?0:m_frame + 1;
                }
            } else if(m_state == FLYING) {
                m_sprite.setTextureRect({27, 9, 9, 9});
            } else {
                m_sprite.setTextureRect({36, 0, 9, 9});
            }
        }
        m_sprite.setPosition(float(m_coord.x - 4.5) * 6, float((82 - m_coord.y) * 6));
        m_game.getWindow().draw(m_sprite);
    }

    sf::Vector2f Player::getCoord() {
        return m_coord;
    }

    int Player::getStamina() {
        return int(m_stamina / 100);
    }

    int Player::getState() {
        return m_state;
    }
}