#ifndef MOUSE_H
#define MOUSE_H

#include "IGuiComponent.h"

namespace av {
    class Game;

    class Mouse: public IGuiComponent {
    public:
        Mouse(Game& game);
        bool update();
        void draw(sf::RenderWindow& window);
        bool handleInput(sf::Event& windowEvent);
        std::string getMessage() {
            return "";
        }
    private:
        sf::Sprite m_spriteMouse;
        bool m_isPressed;
    };
}

#endif