#include "GameStateTitle.h"
#include "Game.h"
#include <iostream>
#include "GameStateGame.h"

namespace av {
    GameStateTitle::GameStateTitle(Game& game):IGameState(game), m_gui(game), m_bot(game) {
        m_background.setTexture(m_game.getTexture("twilight"));
        m_background.setTextureRect({64, 384, 64, 96});
        m_background.setScale({6.0F, 6.0F});
        m_decoration.setTexture(m_game.getTexture("twilight"));
        m_decoration.setTextureRect({0, 0, 64, 96});
        m_decoration.setScale({6.0F, 6.0F});
        m_title.setTexture(m_game.getTexture("title"));
        m_title.setScale({6.0F, 6.0F});
        m_overlay.setTexture(m_game.getTexture("twilight"));
        m_overlay.setTextureRect({0, 96, 64, 96});
        m_overlay.setScale({6.0F, 6.0F});
        m_gui.setCursorVisible(0);
        m_gui.pushComponent(new Button(game, 14 * 6, 56 * 6, 0), 0);
        m_gui.pushComponent(new Button(game, 14 * 6, 69 * 6, 1), 1);
        m_mute = new Mute(game, 1 * 6, 87 * 6);
        m_gui.pushComponent(m_mute, 2);
        m_music.setBuffer(m_game.getSound("title"));
        m_music.play(true);
    }

    GameStateTitle::~GameStateTitle() {
        m_music.stop();
    }

    void GameStateTitle::draw(const double dt) {
        m_game.getWindow().clear(sf::Color::Black);
        m_game.getWindow().draw(m_background);
        m_game.getWindow().draw(m_decoration);
        m_bot.draw();
        m_game.getWindow().draw(m_overlay);
        m_game.getWindow().draw(m_title);
        m_gui.draw();
        m_game.getWindow().display();
    }

    void GameStateTitle::update() {
        m_bot.update();
        switch(m_gui.update()) {
            case 0:
                m_music.stop();
                m_game.changeState(new GameStateGame(m_game));
                return;
            case 1:
                m_game.getWindow().close();
                return;
            case 2:
                if(m_mute->getStatus())
                    m_music.stop();
                else
                    m_music.play(true);
                break;
        }
    }

    void GameStateTitle::handleInput() {
        sf::Event windowEvent;
        while(m_game.getWindow().pollEvent(windowEvent)) {
            m_gui.handleInput(windowEvent);
            switch(windowEvent.type) {
                case sf::Event::Closed:
                    m_music.stop();
                    m_game.getWindow().close();
                    return;
                case sf::Event::KeyPressed:
                    if(windowEvent.key.code == sf::Keyboard::Escape) {
                        m_music.stop();
                        m_game.getWindow().close();
                        return;
                    } else if(windowEvent.key.code == sf::Keyboard::M) {
                        m_mute->setStatus(!m_mute->getStatus());
                        if(m_mute->getStatus()) {
                            m_music.stop();
                        } else {
                            m_music.play(true);
                        }
                        break;
                    }
                    break;
            }
        }
    }
}