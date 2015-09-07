#include "GameStateGame.h"
#include "Game.h"
#include "GameStateTitle.h"

namespace av {
    GameStateGame::GameStateGame(Game& game):IGameState(game), m_gui(game), m_player(game), m_stamina(game, m_player), m_metre(game, m_player) {
        m_background.setTexture(m_game.getTexture("twilight"));
        m_background.setTextureRect({64, 384, 64, 96});
        m_background.setScale({6.0F, 6.0F});
        m_decoration.setTexture(m_game.getTexture("twilight"));
        m_decoration.setTextureRect({0, 0, 64, 96});
        m_decoration.setScale({6.0F, 6.0F});
        m_overlay.setTexture(m_game.getTexture("twilight"));
        m_overlay.setTextureRect({0, 96, 64, 96});
        m_overlay.setScale({6.0F, 6.0F});
        m_gui.setCursorVisible(0);
        m_mute = new Mute(m_game, 1 * 6, 87 * 6);
        m_mute->setStatus(false);
        m_music.setBuffer(m_game.getSound("game"));
        m_music.play(true);
        m_view.setSize(384, 576);
        m_view.setCenter(192, 288);
        m_pauseState = false;
        m_dim.setPosition(0, 0);
        m_dim.setSize({384, 576});
        m_dim.setFillColor(sf::Color(0, 0, 0, 200));
    }

    GameStateGame::~GameStateGame() {
        m_music.stop();
    }

    void GameStateGame::draw(const double dt) {
        m_game.getWindow().clear(sf::Color::Black);
        m_game.getWindow().draw(m_background);
        m_game.getWindow().setView(m_view);
        m_game.getWindow().draw(m_decoration);
        m_player.draw();
        m_game.getWindow().draw(m_overlay);
        m_game.getWindow().setView(m_game.getWindow().getDefaultView());
        m_stamina.draw();
        m_metre.draw();
        if(m_pauseState) {
            m_game.getWindow().draw(m_dim);
            m_gui.draw();
        }
        m_game.getWindow().display();
    }

    void GameStateGame::update() {
        if(!m_pauseState) {
            m_player.update();
            m_stamina.update();
            m_metre.update();
            if(m_player.getCoord().y > 48) {
                m_view.setCenter(192, 288.0F - int((m_player.getCoord().y - 48) * 6));
                m_background.setTextureRect({64, 384 - int(m_player.getCoord().y / 3000 * 384), 64, 96});
            } else {
                m_view.setCenter(192, 288);
                m_background.setTextureRect({64, 384, 64, 96});
            }
        }
        switch(m_gui.update()) {
            case 0:
                if(m_mute->getStatus())
                    m_music.stop();
                else
                    m_music.play(true);
                break;
            case 1:
                m_pauseState = false;
                m_gui.removeComponent(0);
                m_gui.removeComponent(1);
                m_gui.removeComponent(2);
                break;
            case 2:
                m_music.stop();
                m_game.changeState(new GameStateTitle(m_game));
                return;
        }
    }

    void GameStateGame::handleInput() {
        sf::Event windowEvent;
        while(m_game.getWindow().pollEvent(windowEvent)) {
            if(!m_pauseState)
                m_player.handleInput(windowEvent);
            else
                m_gui.handleInput(windowEvent);
            switch(windowEvent.type) {
                case sf::Event::Closed:
                    m_music.stop();
                    m_game.getWindow().close();
                    return;
                case sf::Event::KeyPressed:
                    if(windowEvent.key.code == sf::Keyboard::Escape) {
                        if(m_pauseState) {
                            m_pauseState = false;
                            m_gui.removeComponent(0);
                            m_gui.removeComponent(1);
                            m_gui.removeComponent(2);
                        } else {
                            m_pauseState = true;
                            m_gui.pushComponent(m_mute, 0);
                            m_gui.pushComponent(new Button(m_game, 14 * 6, 54 * 6, 3), 1);
                            m_gui.pushComponent(new Button(m_game, 14 * 6, 69 * 6, 1), 2);
                        }
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