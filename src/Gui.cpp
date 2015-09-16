#include "Gui.h"
#include "Game.h"

namespace av {
    Gui::Gui(Game& game):m_game(game) {
    }

    Gui::~Gui() {
        while(m_components.size() != 0) {
            delete m_components[0];
            m_components.erase(m_components.begin());
        }
    }

    int Gui::update() {
        for(auto& component : m_components) {
            if(component.second->update()) {
                return component.first;
            }
        }
        return -1;
    }

    void Gui::handleInput(sf::Event& windowEvent) {
        for(auto& component : m_components) {
            if(component.second->handleInput(windowEvent))
                return;
        }
    }

    void Gui::draw() {
        for(auto& component : m_components) {
            component.second->draw(m_game.getWindow());
        }
    }

    void Gui::pushComponent(IGuiComponent* component, int id) {
        m_components[id] = component;
    }

    IGuiComponent* Gui::getComponent(int id) {
        return m_components[id];
    }

    void Gui::removeComponent(int id) {
        m_components.erase(id);
    }
}