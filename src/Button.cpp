#include "Button.h"
#include "Game.h"

namespace av {
    Button::Button(Game& game, int x, int y, int id):IGuiComponent(game){
        m_x = x;
        m_y = y;
        m_id = id;
        m_state = IDLE;
        m_sprite.setTexture(game.getTexture("gui"));
        m_sprite.setTextureRect({0, 12 * id, 36, 12});
        m_sprite.setScale({6.0F, 6.0F});
        m_sprite.setPosition(float(x), float(y));
    }

    bool Button::update() {
        if(m_state == RELEASED) {
            m_state = HOVER;
            return true;
        } else {
            return false;
        }
    }

    void Button::draw(sf::RenderWindow& window) {
        window.draw(m_sprite);
    }

    bool Button::handleInput(sf::Event& windowEvent) {
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
                    m_sprite.setTextureRect({36, 12 * m_id, 36, 12});
                }
            } else {
                if(m_state == IDLE || m_state == LEFT) {
                    m_state = HOVER;
                    m_sprite.setTextureRect({0, 12 * m_id, 36, 12});
                } else if(m_state == PRESSED) {
                    m_state = RELEASED;
                    m_sprite.setTextureRect({0, 12 * m_id, 36, 12});
                }
            }
            return true;
        } else {
            if(isLeftPressed) {
                if(m_state == HOVER) {
                    m_state = IDLE;
                    m_sprite.setTextureRect({0, 12 * m_id, 36, 12});
                } else if(m_state == PRESSED) {
                    m_state = LEFT;
                    m_sprite.setTextureRect({0, 12 * m_id, 36, 12});
                }
            } else {
                if(m_state == HOVER || m_state == LEFT) {
                    m_state = IDLE;
                    m_sprite.setTextureRect({0, 12 * m_id, 36, 12});
                }
            }
            return false;
        }
    }
}