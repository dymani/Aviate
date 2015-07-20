#include "Mute.h"
#include "Game.h"

namespace av {
    Mute::Mute(Game& game, int x, int y):IGuiComponent(game) {
        m_x = x;
        m_y = y;
        m_mute = false;
        m_state = IDLE;
        m_sprite.setTexture(game.getTexture("gui"));
        m_sprite.setTextureRect({53, 65, 8, 8});
        m_sprite.setScale({6.0F, 6.0F});
        m_sprite.setPosition(float(x), float(y));
    }

    bool Mute::update() {
        if(m_state == RELEASED) {
            m_state = HOVER;
            m_mute = !m_mute;
            if(m_mute) {
                m_sprite.setTextureRect({63, 65, 8, 8});
            } else {
                m_sprite.setTextureRect({53, 65, 8, 8});
            }
            return true;
        } else {
            return false;
        }
    }

    void Mute::draw(sf::RenderWindow& window) {
        window.draw(m_sprite);
    }

    bool Mute::handleInput(sf::Event& windowEvent) {
        int mouseX = sf::Mouse::getPosition(m_game.getWindow()).x;
        int mouseY = sf::Mouse::getPosition(m_game.getWindow()).y;
        bool isLeftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        bool isHover = mouseX > m_x
            && mouseX < m_x + WIDTH
            && mouseY > m_y
            && mouseY < m_y + HEIGHT;
        if(isHover) {
            if(isLeftPressed) {
                if(m_state == HOVER || m_state == LEFT) {
                    m_state = PRESSED;
                }
            } else {
                if(m_state == IDLE || m_state == LEFT) {
                    m_state = HOVER;
                } else if(m_state == PRESSED) {
                    m_state = RELEASED;
                }
            }
            return true;
        } else {
            if(isLeftPressed) {
                if(m_state == HOVER) {
                    m_state = IDLE;
                } else if(m_state == PRESSED) {
                    m_state = LEFT;
                }
            } else {
                if(m_state == HOVER || m_state == LEFT) {
                    m_state = IDLE;
                }
            }
            return false;
        }
    }

    bool Mute::getStatus() {
        return m_mute;
    }
}