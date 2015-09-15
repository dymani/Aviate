#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>

namespace av {
    class Game;
    class Player;

    class Level {
    public:
        Level(Game& game, Player& player);
        void update();
        void draw();
    private:
        Game& m_game;
        Player& m_player;
        sf::Sprite m_sprite, m_digit;
        int m_level;
    };
}

#endif