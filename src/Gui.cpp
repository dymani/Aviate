#include "Gui.h"
#include "Game.h"

namespace av {
    Gui::Gui(Game& game):m_game(game), m_mouse(game) {
        setCursorVisible(true);
    }

    int Gui::update() {
        m_mouse.update();
        for(auto& component : m_components) {
            if(component.second->update()) {
                return component.first;
            }
        }
        return -1;
    }

    void Gui::handleInput(sf::Event& windowEvent) {
        m_mouse.handleInput(windowEvent);
        for(auto& component : m_components) {
            if(component.second->handleInput(windowEvent))
                return;
        }
    }

    void Gui::draw() {
        for(auto& component : m_components) {
            component.second->draw(m_game.getWindow());
        }
        if(m_isCursorVisible == true) {
            m_mouse.draw(m_game.getWindow());
        }
    }

    void Gui::pushComponent(IGuiComponent* component, int id) {
        m_components[id] = component;
    }

    void Gui::removeComponent(int id) {
        m_components.erase(id);
    }

    void Gui::setCursorVisible(bool isCursorVisible) {
        m_isCursorVisible = isCursorVisible;
        m_game.getWindow().setMouseCursorVisible(!isCursorVisible);
    }
}