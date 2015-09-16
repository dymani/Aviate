#ifndef I_GUI_COMPONENT
#define I_GUI_COMPONENT

#include <string>
#include <SFML/Graphics.hpp>

namespace av {
    class Game;

    class IGuiComponent {
    public:
        IGuiComponent(Game& game):m_game(game) {
        }
        virtual bool update() = 0;
        virtual void draw(sf::RenderWindow& window) = 0;
        virtual bool handleInput(sf::Event& windowEvent) = 0;
    protected:
        Game& m_game;
        int m_x, m_y;
    };
}

#endif