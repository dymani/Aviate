#ifndef BOT_H
#define BOT_H

#include <SFML/Graphics.hpp>

namespace av {
    class Game;

    class Bot {
    public:
        Bot(Game& game);
        void update();
        void draw();
    private:
        Game& m_game;
        sf::Vector2f m_coord;
        sf::Sprite m_sprite;
        int m_finishingTicks;
        enum Direction { LEFT, RIGHT, IDLE } m_direction;
        bool m_left;
        int m_frame;
        int m_tickToFrame;
    };
}

#endif