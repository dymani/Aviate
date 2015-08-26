#include "GameStateGame.h"
#include "Game.h"
#include "GameStateTitle.h"

namespace av {
    GameStateGame::GameStateGame(Game& game):IGameState(game), m_gui(game), m_player(game) {
        m_background.setTexture(m_game.getTexture("twilight"));
        m_background.setTextureRect({64, 0, 64, 96});
        m_background.setScale({6.0F, 6.0F});
        m_decoration.setTexture(m_game.getTexture("twilight"));
        m_decoration.setTextureRect({0, 0, 64, 96});
        m_decoration.setScale({6.0F, 6.0F});
        m_overlay.setTexture(m_game.getTexture("twilight"));
        m_overlay.setTextureRect({128, 0, 64, 96});
        m_overlay.setScale({6.0F, 6.0F});
        m_gui.setCursorVisible(0);
        m_mute = new Mute(game, 1 * 6, 87 * 6);
        m_gui.pushComponent(m_mute, 0);
        m_music.setBuffer(m_game.getSound("game"));
        m_music.play(true);
    }

    GameStateGame::~GameStateGame() {
        m_music.stop();
    }

    void GameStateGame::draw(const double dt) {
        m_game.getWindow().clear(sf::Color::Black);
        m_game.getWindow().draw(m_background);
        m_game.getWindow().draw(m_decoration);
        m_player.draw();
        m_game.getWindow().draw(m_overlay);
        m_gui.draw();
        m_game.getWindow().display();
    }

    void GameStateGame::update() {
        m_player.update();
        switch(m_gui.update()) {
            case 0:
                if(m_mute->getStatus())
                    m_music.stop();
                else
                    m_music.play(true);
                break;
        }
    }

    void GameStateGame::handleInput() {
        sf::Event windowEvent;
        while(m_game.getWindow().pollEvent(windowEvent)) {
            m_gui.handleInput(windowEvent);
            m_player.handleInput(windowEvent);
            switch(windowEvent.type) {
                case sf::Event::Closed:
                    m_music.stop();
                    m_game.getWindow().close();
                    return;
                case sf::Event::KeyPressed:
                    if(windowEvent.key.code == sf::Keyboard::Escape) {
                        m_music.stop();
                        m_game.changeState(new GameStateTitle(m_game));
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