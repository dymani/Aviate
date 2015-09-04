#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#define PI 3.14159265

namespace av {
    class Game;

    class Player {
    public:
        Player(Game& game);
        void update();
        void handleInput(sf::Event& windowEvent);
        void draw();
        sf::Vector2f getCoord();
    protected:
        Game& m_game;
        sf::Vector2f m_coord;
        enum State { IDLE, FLYING, FALLING } m_state;
        sf::Vector2f m_velocity;
        float m_speedX, m_speedY, GRAVITY;
        bool m_facingLeft;
        sf::Sprite m_sprite;
        bool m_spaceState;
    };
}

#endif