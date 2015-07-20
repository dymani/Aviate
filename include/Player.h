#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

namespace av {
    class Game;

    class Player {
    public:
        Player(Game& game);
        void update();
        void handleInput(sf::Event& windowEvent);
        void draw();
    protected:
        Game& m_game;
        sf::Vector2f m_coord, m_newCoord;
        bool m_facingLeft, m_moving, m_flying;
        sf::Sprite m_sprite;
    };
}

#endif