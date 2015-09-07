#ifndef METRE_H
#define METRE_H

#include <SFML/Graphics.hpp>

namespace av {
    class Game;
    class Player;

    class Metre {
    public:
        Metre(Game& game, Player& player);
        void update();
        void draw();
    private:
        Game& m_game;
        Player& m_player;
        float m_height;
        sf::Sprite m_metre, m_icon;
    };
}

#endif