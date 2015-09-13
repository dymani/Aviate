#ifndef BP_COUNTER_H
#define BP_COUNTER_H

#include <SFML/Graphics.hpp>

namespace av {
    class Game;
    class Player;

    class BpCounter {
    public:
        BpCounter(Game& game, Player& player);
        void update();
        void draw();
    private:
        Game& m_game;
        Player& m_player;
        sf::Sprite m_sprite, m_digit;
        int m_bp;
    };
}

#endif