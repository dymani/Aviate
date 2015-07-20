#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <map>

#include "IGuiComponent.h"
#include "Mouse.h"

namespace av {
    class Game;

    class Gui {
    public:
        Gui(Game& game);
        int update();
        void handleInput(sf::Event& windowEvent);
        void draw();
        void pushComponent(IGuiComponent* component, int id);
        IGuiComponent* getComponent(int id);
        void removeComponent(int id);
        void setCursorVisible(bool isCursorVisible);
    private:
        Game& m_game;
        Mouse m_mouse;
        std::map<int, IGuiComponent*> m_components;
        bool m_isCursorVisible = true;
    };
}

#endif