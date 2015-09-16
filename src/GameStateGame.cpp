#include "GameStateGame.h"
#include "Game.h"
#include "GameStateTitle.h"
#include "GameStateEnd.h"

namespace av {
    GameStateGame::GameStateGame(Game& game, bool mute, bool tutorial):IGameState(game), m_gui(game),
        m_player(game, m_buffs),
        m_stamina(game, m_player), m_metre(game, m_player), m_bpCounter(game, m_player),
        m_level(game, m_player) {
        m_background.setTexture(m_game.getTexture("twilight"));
        m_background.setTextureRect({64, 384, 64, 96});
        m_background.setScale({6.0F, 6.0F});
        m_decoration.setTexture(m_game.getTexture("twilight"));
        m_decoration.setTextureRect({0, 0, 64, 96});
        m_decoration.setScale({6.0F, 6.0F});
        m_overlay.setTexture(m_game.getTexture("twilight"));
        m_overlay.setTextureRect({0, 96, 64, 96});
        m_overlay.setScale({6.0F, 6.0F});
        m_tutorial.setTexture(m_game.getTexture("tutorial"));
        m_tutorial.setScale(6.0F, 6.0F);
        m_game.getWindow().setMouseCursorVisible(true);
        m_mute = new Mute(m_game, 1 * 6, 87 * 6);
        m_mute->setStatus(false);
        m_music.setBuffer(m_game.getSound("game"));
        if(mute) {
            m_mute->setStatus(true);
        } else {
            m_music.play(true);
            m_mute->setStatus(false);
        }
        m_view.setSize(384, 576);
        m_view.setCenter(192, 288);
        if(tutorial)
            m_state = TUT;
        else
            m_state = GAME;
        m_dim.setPosition(0, 0);
        m_dim.setSize({384, 576});
        m_dim.setFillColor(sf::Color(0, 0, 0, 200));
        m_buffs.clear();
        m_viewCoord = 0;
        m_viewVelocity = 0;
        m_viewSpeed = 0;
        m_generated = 0;
        m_lastBuff = -1;
    }

    GameStateGame::~GameStateGame() {
        delete m_mute;
        m_music.stop();
    }

    void GameStateGame::update() {
        switch(m_state) {
            case GAME:
                if(m_player.update()) {
                    m_state = END;
                    m_stamina.end();
                }
                m_metre.update();
                m_bpCounter.update();
                m_level.update();
            case END:
                if(m_stamina.update()) {
                    m_music.stop();
                    m_game.changeState(new GameStateEnd(m_game, m_buffs, m_player.getCoord(), m_player.getBp(), m_mute->getStatus()));
                    return;
                }
                int destination;
                if(m_player.getState() == 0) {
                    destination = 0;
                } else if(m_player.getState() == 1) {
                    destination = int(m_player.getCoord().y + 0.5F) - 48;
                } else {
                    destination = int(m_player.getCoord().y + 0.5F) - 40;
                }
                if(destination > m_viewCoord) {
                    m_viewSpeed = 10 * (destination - m_viewCoord) / 48 * m_player.getLevelSpeed();
                    m_viewVelocity += 0.5F;
                    m_viewVelocity = m_viewVelocity > m_viewSpeed?m_viewSpeed:m_viewVelocity;
                } else if(destination < m_viewCoord) {
                    m_viewSpeed = 20 * (destination - m_viewCoord) / 48;
                    m_viewVelocity -= 0.5F;
                    m_viewVelocity = m_viewVelocity < m_viewSpeed?m_viewSpeed:m_viewVelocity;
                }
                m_viewCoord += m_viewVelocity;
                if(m_viewCoord < 0)m_viewCoord = 0;
                if(m_state == GAME) {
                    while((m_player.getCoord().y + 100) > m_generated * 20 && m_generated < 150) {
                        int x = rand() % 64;
                        m_buffs.push_back(new Buff(m_game, m_player, {x, (m_generated + 1) * 20},
                            rand() % 100 > 25?0:1));
                        if(m_lastBuff != -1) {
                            int sx, sy;
                            for(int i = 1; i < 5; i++) {
                                sx = int((x - m_lastBuff) / 5 * i) + m_lastBuff;
                                sy = m_generated * 20 + 4 * i;
                                m_buffs.push_back(new Buff(m_game, m_player, {sx, sy}, 2));
                            }
                        }
                        m_lastBuff = x;
                        m_generated++;
                    }
                }
                break;
        }
        switch(m_gui.update()) {
            case 0:
                if(m_mute->getStatus())
                    m_music.stop();
                else
                    m_music.play(true);
                break;
            case 1:
                m_state = GAME;
                m_gui.removeComponent(0);
                m_gui.removeComponent(1);
                m_gui.removeComponent(2);
                break;
            case 2:
                m_music.stop();
                m_game.changeState(new GameStateTitle(m_game, m_mute->getStatus()));
                return;
        }
    }

    void GameStateGame::draw(const double dt) {
        m_game.getWindow().clear(sf::Color::Black);
        m_game.getWindow().draw(m_background);
        m_view.setCenter(192, float(int(288.0F - m_viewCoord * 6)));
        m_background.setTextureRect({64, 384 - int(m_viewCoord / 3000 * 384), 64, 96});
        m_game.getWindow().setView(m_view);
        m_game.getWindow().draw(m_decoration);
        m_player.draw();
        for(auto& buff : m_buffs) {
            buff->draw();
        }
        m_game.getWindow().draw(m_overlay);
        m_game.getWindow().setView(m_game.getWindow().getDefaultView());
        m_stamina.draw();
        m_metre.draw();
        m_bpCounter.draw();
        m_level.draw();
        if(m_state == PAUSE) {
            m_game.getWindow().draw(m_dim);
            m_gui.draw();
        } else if(m_state == TUT) {
            m_game.getWindow().draw(m_tutorial);
        }
        m_game.getWindow().display();
    }

    void GameStateGame::handleInput() {
        sf::Event windowEvent;
        while(m_game.getWindow().pollEvent(windowEvent)) {
            switch(m_state) {
                case GAME:
                    m_player.handleInput(windowEvent);
                    break;
                case PAUSE:
                    m_gui.handleInput(windowEvent);
                    break;
            }
            switch(windowEvent.type) {
                case sf::Event::Closed:
                    m_music.stop();
                    m_game.getWindow().close();
                    return;
                case sf::Event::KeyPressed:
                    if(windowEvent.key.code == sf::Keyboard::Escape) {
                        if(m_state == PAUSE) {
                            m_state = GAME;
                            m_gui.removeComponent(0);
                            m_gui.removeComponent(1);
                            m_gui.removeComponent(2);
                        } else if(m_state == GAME) {
                            m_state = PAUSE;
                            m_gui.pushComponent(m_mute, 0);
                            m_gui.pushComponent(new Button(m_game, 14 * 6, 54 * 6, 3), 1);
                            m_gui.pushComponent(new Button(m_game, 14 * 6, 69 * 6, 1), 2);
                        } else if(m_state == TUT) {
                            m_state = GAME;
                        }
                    } else if(windowEvent.key.code == sf::Keyboard::M) {
                        m_mute->setStatus(!m_mute->getStatus());
                        if(m_mute->getStatus()) {
                            m_music.stop();
                        } else {
                            m_music.play(true);
                        }
                        break;
                    } else if(windowEvent.key.code == sf::Keyboard::Return
                        || windowEvent.key.code == sf::Keyboard::Space) {
                        if(m_state == TUT) {
                            m_state = GAME;
                        }
                    }
                    break;
            }
        }
    }

}