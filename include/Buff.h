#ifndef BUFF_H
#define BUFF_H

#include "SFML/Graphics.hpp"

namespace av {
    class Game;
    class Player;

    class Buff {
    public:
        Buff(Game& game, Player& player, sf::Vector2i coord, int type);
        void update();
        void draw();
        void collect();
        sf::Vector2i getCoord();
        sf::FloatRect getCollisionBox();
    private:
        Game& m_game;
        Player& m_player;
        sf::Vector2i m_coord;
        sf::Sprite m_sprite;
        enum TYPE {
            BP, LVL, STM
        } m_type;
    };
}

#endif