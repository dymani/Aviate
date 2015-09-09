#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#define PI 3.14159265

namespace av {
    class Game;
    class Buff;

    class Player {
    public:
        Player(Game& game, std::vector<Buff*>& buffs);
        void update();
        void handleInput(sf::Event& windowEvent);
        void draw();
        sf::Vector2f getCoord();
        int getStamina();
        void setStamina(int stamina);
        int getState();
    protected:
        Game& m_game;
        sf::Vector2f m_coord;
        enum State { IDLE, FLYING, FALLING } m_state;
        sf::Vector2f m_velocity;
        float m_speedX, m_speedY, GRAVITY;
        bool m_facingLeft;
        sf::Sprite m_sprite;
        bool m_spaceState;
        int m_stamina;
        int m_frame, m_interval;
        std::vector<Buff*>& m_buffs;
    };
}

#endif