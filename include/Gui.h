#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <map>

#include "IGuiComponent.h"

namespace av {
    class Game;

    class Gui {
    public:
        Gui(Game& game);
        ~Gui();
        int update();
        void handleInput(sf::Event& windowEvent);
        void draw();
        void pushComponent(IGuiComponent* component, int id);
        IGuiComponent* getComponent(int id);
        void removeComponent(int id);
    private:
        Game& m_game;
        std::map<int, IGuiComponent*> m_components;
    };
}

#endif