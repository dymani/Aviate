#ifndef MUTE_H
#define MUTE_H

#include "IGuiComponent.h"

namespace av {
    class Mute: public IGuiComponent {
    public:
        const static int WIDTH = 8 * 6, HEIGHT = 8 * 6;
        Mute(Game& game, int x, int y);
        bool update();
        void draw(sf::RenderWindow& window);
        bool handleInput(sf::Event& windowEvent);
        bool getStatus();
        void setStatus(bool mute);
    private:
        enum ButtonState {
            IDLE, HOVER, PRESSED, LEFT, RELEASED
        } m_state;
        bool m_mute;
        sf::Sprite m_sprite;
    };
}

#endif