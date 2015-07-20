#ifndef GAME_H
#define GAME_H

#include <time.h> 
#include <stack>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

namespace av {
    class IGameState;

    class Game {
    public:
        static const int MS_PER_UPDATE = 20;

        Game();
        ~Game();
        int run();

        void pushState(IGameState* state);
        void popState();
        void changeState(IGameState* state);
        IGameState* peekState();

        sf::RenderWindow& getWindow();

        void pushTexture(std::string name, sf::Texture& texture);
        sf::Texture& getTexture(std::string name);

        void pushSound(std::string name, sf::SoundBuffer& sound);
        sf::SoundBuffer& getSound(std::string name);
    private:
        std::stack<IGameState*> m_states;
        sf::RenderWindow m_window;
        sf::ContextSettings m_settings;
        sf::Texture m_icon;
        std::map<std::string, sf::Texture> m_textures;
        std::map<std::string, sf::SoundBuffer> m_sounds;
    };
}

#endif