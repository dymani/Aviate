#include "Mouse.h"
#include "Game.h"

namespace av {
    Mouse::Mouse(Game& game):IGuiComponent(game) {
        m_spriteMouse.setTexture(m_game.getTexture("gui"));
        m_spriteMouse.setScale(2, 2);
        m_x = sf::Mouse::getPosition(m_game.getWindow()).x;
        m_y = sf::Mouse::getPosition(m_game.getWindow()).y;
        m_spriteMouse.setPosition(float(m_x), float(m_y));
        m_spriteMouse.setTextureRect(sf::IntRect(0, 84, 16, 16));
    }

    bool Mouse::update() {
        return false;
    }

    void Mouse::draw(sf::RenderWindow& window) {
        if(m_x >= 0 && m_x < 1280
            && m_y >= 0 && m_y < 720)
            window.draw(m_spriteMouse);
    }

    bool Mouse::handleInput(sf::Event& windowEvent) {
        m_x = sf::Mouse::getPosition(m_game.getWindow()).x;
        m_y = sf::Mouse::getPosition(m_game.getWindow()).y;
        m_spriteMouse.setPosition(float(m_x), float(m_y));
        m_isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left)
            || sf::Mouse::isButtonPressed(sf::Mouse::Right);
        if(m_isPressed)
            m_spriteMouse.setTextureRect(sf::IntRect(16, 84, 16, 16));
        else
            m_spriteMouse.setTextureRect(sf::IntRect(0, 84, 16, 16));
        return false;
    }
}