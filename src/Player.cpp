#include "Player.h"
#include "Game.h"
#include "Buff.h"

namespace av {
    Player::Player(Game& game, std::vector<Buff*>& buffs):m_game(game), m_buffs(buffs) {
        m_coord = {32, 0};
        m_state = IDLE;
        m_velocity = {0, 0};
        m_speedX = m_speedY = 0;
        GRAVITY = 0.2F;
        m_facingLeft = true;
        m_sprite.setTexture(game.getTexture("sprite"));
        m_sprite.setScale({6.0F, 6.0F});
        m_sprite.setTextureRect({9, 0, 9, 9});
        m_sprite.setOrigin(4.5F, 0.0F);
        m_sprite.setPosition(float(m_coord.x * 6), float(82 * 6));
        m_spaceState = false;
        m_frame = 1;
        m_interval = 0;
        m_stamina = 10000;
        m_bp = 0;
        m_level = 1;
        m_levelSpeed = {1.0F, 1.1F, 1.21F, 1.33F, 1.46F, 1.61F, 1.77F, 1.95F, 2.14F, 2.36F};
        m_gameover = false;
    }

    bool Player::update() {
        sf::Vector2f coord = m_coord;
        int mouseX = int(sf::Mouse::getPosition(m_game.getWindow()).x / 6);
        if(mouseX > coord.x) {
            if(mouseX - coord.x > 0.1) {
                m_facingLeft = false;
                m_speedX = 10.0F * (mouseX - coord.x) / 64 * getLevelSpeed();
                m_velocity.x += 0.5F;
                m_velocity.x = m_velocity.x > m_speedX?m_speedX:m_velocity.x;
            }
        } else if(mouseX < coord.x) {
            if(coord.x - mouseX > 0.1) {
                m_facingLeft = true;
                m_speedX = -10.0F * (coord.x - mouseX) / 64 * getLevelSpeed();
                m_velocity.x -= 0.5F;
                m_velocity.x = m_velocity.x < m_speedX?m_speedX:m_velocity.x;
            }
        }
        coord.x += m_velocity.x;
        switch(m_state) {
            case IDLE:
                if(coord.x <= 0) {
                    coord.x = 0;
                } else if(coord.x >= 64) {
                    coord.x = 64;
                }
                if(m_stamina <= 0)
                    m_gameover = true;
                break;
            case FALLING:
                m_speedY -= GRAVITY;
                m_speedY = m_speedY < -10?-10:m_speedY;
            case FLYING:
                if(m_state == FLYING)
                    m_velocity.y = sqrt(150.0F - m_velocity.x * m_velocity.x) * m_speedY / 10
                    * getLevelSpeed();
                else
                    m_velocity.y = sqrt(150.0F - m_velocity.x * m_velocity.x) * m_speedY / 10;
                if(coord.y + m_velocity.y > 0) {
                    coord.y += m_velocity.y;
                } else {
                    if(m_speedY == -10)
                        m_gameover = true;
                    coord.y = 0;
                    m_speedY = 0;
                    m_velocity.y = 0;
                    m_state = IDLE;
                }
                if(m_state == FLYING)
                    m_stamina -= int(m_velocity.y * 50 * getLevelSpeed());
                if(coord.x <= 0) {
                    coord.x = 0;
                } else if(coord.x >= 64) {
                    coord.x = 64;
                }
                if(coord.y > 3000)
                    m_gameover = true;
                sf::FloatRect collisionBox = {coord.x - 1.5F, coord.y - 1.0F, 3, 8};
                for(unsigned int i = 0; i < m_buffs.size();) {
                    if(collisionBox.intersects(m_buffs.at(i)->getCollisionBox())) {
                        m_buffs.at(i)->collect();
                        m_buffs.erase(m_buffs.begin() + i);
                        continue;
                    }
                    i++;
                }
                break;
        }
        m_coord = coord;
        m_interval++;
        if(m_stamina < 0) m_stamina = 0;
        return m_gameover;
    }

    void Player::handleInput(sf::Event& windowEvent) {
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
                    m_speedY = 0.5F;
                    m_stamina -= int(100 * getLevelSpeed());
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
        if(m_gameover) {
            m_sprite.setTextureRect({45, 0, 9, 9});
            m_sprite.setPosition(float(int(m_coord.x * 6)), float(int((82 - m_coord.y) * 6)));
            m_game.getWindow().draw(m_sprite);
            return;
        }
        if(m_facingLeft) {
            if(m_velocity.x > -0.2 && m_state == IDLE) {
                m_sprite.setTextureRect({9, 0, 9, 9});
            } else if(m_state == IDLE) {
                switch(m_frame) {
                    case 0:
                        m_sprite.setTextureRect({0, 0, 9, 9});
                        break;
                    case 1:
                    case 3:
                        m_sprite.setTextureRect({9, 0, 9, 9});
                        break;
                    case 2:
                        m_sprite.setTextureRect({18, 0, 9, 9});
                        break;
                }
                if(m_interval >= 10) {
                    m_frame = m_frame == 3?0:m_frame + 1;
                    m_interval = 0;
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
                    case 3:
                        m_sprite.setTextureRect({9, 9, 9, 9});
                        break;
                    case 2:
                        m_sprite.setTextureRect({18, 9, 9, 9});
                        break;
                }
                if(m_interval >= 10) {
                    m_frame = m_frame == 3?0:m_frame + 1;
                    m_interval = 0;
                }
            } else if(m_state == FLYING) {
                m_sprite.setTextureRect({27, 9, 9, 9});
            } else {
                m_sprite.setTextureRect({36, 0, 9, 9});
            }
        }
        m_sprite.setPosition(float(int(m_coord.x * 6)), float(int((82 - m_coord.y) * 6)));
        m_game.getWindow().draw(m_sprite);
    }

    sf::Vector2f Player::getCoord() {
        return m_coord;
    }

    sf::Vector2f Player::getVelocity() {
        return m_velocity;
    }

    int Player::getStamina() {
        return m_stamina;
    }

    void Player::setStamina(int stamina) {
        if(stamina > 10000)
            stamina = 10000;
        else if(stamina < 0)
            stamina = 0;
        m_stamina = stamina;
    }

    int Player::getState() {
        return m_state;
    }

    int Player::getBp() {
        return m_bp;
    }

    void Player::setBp(int bp) {
        m_bp = bp;
    }

    int Player::getLevel() {
        return m_level;
    }

    void Player::setLevel(int level) {
        if(level > 0 && level <= 10)
            m_level = level;
    }

    float Player::getLevelSpeed(int level) {
        if(level == 0) level = m_level;
        if(level < 0 || level > 10) return 1;
        return m_levelSpeed[level - 1];
    }
}