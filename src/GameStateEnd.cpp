#include "GameStateEnd.h"
#include "Game.h"
#include "GameStateTitle.h"
#include "GameStateGame.h"

namespace av {
    GameStateEnd::GameStateEnd(Game& game, std::vector<Buff*>& buffs, sf::Vector2f player, int bp)
        :IGameState(game), m_game(game), m_buffs(buffs), m_gui(game), m_score(game, bp) {
        m_background.setTexture(m_game.getTexture("twilight"));
        m_background.setTextureRect({64, 384, 64, 96});
        m_background.setScale({6.0F, 6.0F});
        m_decoration.setTexture(m_game.getTexture("twilight"));
        m_decoration.setTextureRect({0, 0, 64, 96});
        m_decoration.setScale({6.0F, 6.0F});
        m_overlay.setTexture(m_game.getTexture("twilight"));
        m_overlay.setTextureRect({0, 96, 64, 96});
        m_overlay.setScale({6.0F, 6.0F});
        m_end.setTexture(m_game.getTexture("end"));
        m_end.setScale({6.0F, 6.0F});
        m_player.setTexture(m_game.getTexture("sprite"));
        m_player.setTextureRect({45, 0, 9, 9});
        m_player.setScale({6.0F, 6.0F});
        m_player.setPosition(float(int(player.x * 6 - 4.5F)), float(int((82 - player.y) * 6)));
        m_gui.setCursorVisible(false);
        m_mute = new Mute(m_game, 1 * 6, 87 * 6);
        m_gui.pushComponent(m_mute, 0);
        m_gui.pushComponent(new Button(game, 14 * 6, 56 * 6, 2), 1);
        m_gui.pushComponent(new Button(game, 14 * 6, 69 * 6, 1), 2);
        m_music.setBuffer(m_game.getSound("title"));
        m_music.play(true);
        for(unsigned int i = 0; i < m_buffs.size();) {
            if(m_buffs.at(i)->getCoord().y > 100) {
                m_buffs.erase(m_buffs.begin() + i);
                continue;
            }
            i++;
        }
    }

    GameStateEnd::~GameStateEnd() {
        m_music.stop();
    }

    void GameStateEnd::update() {
        switch(m_gui.update()) {
            case 0:
                if(m_mute->getStatus())
                    m_music.stop();
                else
                    m_music.play(true);
                break;
            case 1:
                m_music.stop();
                m_game.changeState(new GameStateGame(m_game));
                return;
            case 2:
                m_music.stop();
                m_game.changeState(new GameStateTitle(m_game));
                return;
        }
    }

    void GameStateEnd::draw(const double dt) {
        m_game.getWindow().clear(sf::Color::Black);
        m_game.getWindow().draw(m_background);
        m_game.getWindow().draw(m_decoration);
        m_game.getWindow().draw(m_player);
        m_game.getWindow().draw(m_overlay);
        m_game.getWindow().draw(m_end);
        m_score.draw();
        m_gui.draw();
        m_game.getWindow().display();
    }

    void GameStateEnd::handleInput() {
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