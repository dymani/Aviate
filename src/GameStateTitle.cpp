#include "GameStateTitle.h"
#include "Game.h"
#include <iostream>

namespace av {
    GameStateTitle::GameStateTitle(Game& game):IGameState(game), m_gui(game) {
        m_background.setTexture(m_game.getTexture("twilight"));
        m_background.setTextureRect({64, 0, 64, 96});
        m_background.setScale({6.0F, 6.0F});
        m_overlay.setTexture(m_game.getTexture("twilight"));
        m_overlay.setTextureRect({0, 0, 64, 96});
        m_overlay.setScale({6.0F, 6.0F});
        m_title.setTexture(m_game.getTexture("title"));
        m_title.setScale({6.0F, 6.0F});
        m_gui.setCursorVisible(true);
        m_gui.pushComponent(new Button(game, 14 * 6, 54 * 6, 0), 0);
        m_gui.pushComponent(new Button(game, 14 * 6, 74 * 6, 1), 1);
    }

    void GameStateTitle::draw(const double dt) {
        m_game.getWindow().clear(sf::Color::Black);
        m_game.getWindow().draw(m_background);
        m_game.getWindow().draw(m_overlay);
        m_game.getWindow().draw(m_title);
        m_gui.draw();
        m_game.getWindow().display();
    }

    void GameStateTitle::update() {
        switch(m_gui.update()) {
            case 0:
                std::cout << "pressed\n";
                break;
            case 1:
                m_game.getWindow().close();
                return;
        }
    }

    void GameStateTitle::handleInput() {
        sf::Event windowEvent;
        while(m_game.getWindow().pollEvent(windowEvent)) {
            m_gui.handleInput(windowEvent);
            switch(windowEvent.type) {
                case sf::Event::Closed:
                    m_game.getWindow().close();
                    return;
                case sf::Event::KeyPressed:
                    if(windowEvent.key.code == sf::Keyboard::Escape) {
                        m_game.getWindow().close();
                        return;
                    }
                    break;
            }
        }
    }
}