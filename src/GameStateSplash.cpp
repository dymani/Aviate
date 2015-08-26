#include "GameStateSplash.h"
#include "Game.h"
#include "GameStateTitle.h"

namespace av {
    GameStateSplash::GameStateSplash(Game& game):IGameState(game) {
        {
            sf::Texture splash0, splash1, gui, sprite, title, twilight;
            if(!splash0.loadFromFile("assets/textures/splash0.png")
                || !splash1.loadFromFile("assets/textures/splash1.png")
                || !gui.loadFromFile("assets/textures/gui.png")
                || !sprite.loadFromFile("assets/textures/sprite.png")
                || !title.loadFromFile("assets/textures/title.png")
                || !twilight.loadFromFile("assets/textures/twilight.png")) {
                m_game.getWindow().close();
            }
            m_game.pushTexture("splash0", splash0);
            m_game.pushTexture("splash1", splash1);
            m_game.pushTexture("gui", gui);
            m_game.pushTexture("sprite", sprite);
            m_game.pushTexture("title", title);
            m_game.pushTexture("twilight", twilight);
        }
        {
            sf::SoundBuffer title, game;
            if(!title.loadFromFile("assets/sounds/title.wav")
                || !game.loadFromFile("assets/sounds/game.wav")) {
                m_game.getWindow().close();
            }
            m_game.pushSound("title", title);
            m_game.pushSound("game", game);

        }
        m_splash.setTexture(game.getTexture("splash0"));
        m_splash.setPosition(0, 0);
        m_splash.setColor(sf::Color::Black);
        m_splash.setScale({6.0F, 6.0F});
        m_brightness = 0;
        m_state = START;
        m_splashNo = 0;
    }
    
    void GameStateSplash::draw(const double dt) {
        m_splash.setColor(sf::Color(m_brightness + int(dt * 3), m_brightness + int(dt * 3),
            m_brightness + int(dt * 3), 255));
        m_game.getWindow().clear(sf::Color::Magenta);
        m_game.getWindow().draw(m_splash);
        m_game.getWindow().display();
    }

    void GameStateSplash::update() {
        switch(m_state) {
            case START:
                m_brightness += 5;
                if(m_brightness >= 255) {
                    m_brightness = 255;
                    m_state = PAUSE;
                    m_splashPauseCount = 0;
                    return;
                }
                break;
            case PAUSE:
                m_splashPauseCount++;
                if(m_splashPauseCount >= 10) {
                    m_state = END;
                }
                break;
            case END:
                m_brightness -= 5;
                if(m_brightness <= 0) {
                    m_brightness = 0;
                    if(m_splashNo == 0) {
                        m_state = START;
                        m_splash.setTexture(m_game.getTexture("splash1"));
                        m_splashNo = 1;
                    } else {
                        m_game.changeState(new GameStateTitle(m_game));
                    }
                    return;
                }
                break;
        }
    }

    void GameStateSplash::handleInput() {
        sf::Event windowEvent;
        while(m_game.getWindow().pollEvent(windowEvent)) {
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