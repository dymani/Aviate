#include "Game.h"
#include "IGameState.h"

namespace av {
    Game::Game() {
        m_settings.depthBits = 24;
        m_settings.stencilBits = 8;
        m_settings.antialiasingLevel = 2;
        m_settings.majorVersion = 3;
        m_settings.minorVersion = 0;
        m_window.create(sf::VideoMode(64 * 6, 96 * 6), "Aviate v1.0", sf::Style::Close, m_settings);
        m_window.setKeyRepeatEnabled(true);
        m_icon.loadFromFile("assets/textures/icon.png");
        m_window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.copyToImage().getPixelsPtr());
        m_window.clear(sf::Color::Black);
        srand((unsigned)time(NULL));
    }

    Game::~Game() {
        while(!m_states.empty()) popState();
    }

    int Game::run() {
        clock_t previous, lag, current, elapsed;
        previous = clock();
        lag = 0;
        while(m_window.isOpen()) {
            current = clock();
            elapsed = current - previous;
            previous = current;
            lag += elapsed;

            if(peekState() == nullptr) continue;
            peekState()->handleInput();

            while(lag >= MS_PER_UPDATE) {
                peekState()->update();
                lag -= MS_PER_UPDATE;
            }

            peekState()->draw(lag / MS_PER_UPDATE);
        }
        return 0;
    }

    void Game::pushState(IGameState* state) {
        m_states.push(state);
        return;
    }

    void Game::popState() {
        delete m_states.top();
        m_states.pop();
        return;
    }

    void Game::changeState(IGameState* state) {
        if(!m_states.empty()) {
            popState();
        }
        pushState(state);
        return;
    }

    IGameState* Game::peekState() {
        if(m_states.empty()) return nullptr;
        return m_states.top();
    }

    sf::RenderWindow& Game::getWindow() {
        return m_window;
    }

    void Game::pushTexture(std::string name, sf::Texture& texture) {
        m_textures[name] = texture;
    }

    sf::Texture& Game::getTexture(std::string name) {
        return m_textures[name];
    }

    void Game::pushSound(std::string name, sf::SoundBuffer& sound) {
        m_sounds[name] = sound;
    }

    sf::SoundBuffer& Game::getSound(std::string name) {
        return m_sounds[name];
    }
}