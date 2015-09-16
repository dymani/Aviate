#ifndef BUTTON_H
#define BUTTON_H

#include "IGuiComponent.h"

namespace av {
    class Button: public IGuiComponent {
    public:
        const static int WIDTH = 216, HEIGHT = 72;
        Button(Game& game, int x, int y, int id);
        bool update();
        void draw(sf::RenderWindow& window);
        bool handleInput(sf::Event& windowEvent);
    private:
        enum ButtonState {
            IDLE, HOVER, PRESSED, LEFT, RELEASED
        } m_state;
        int m_id;
        sf::Sprite m_sprite;
    };
}

#endif