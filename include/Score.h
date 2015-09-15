#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>

namespace av {
    class Game;

    class Score {
    public:
        Score(Game& game, int bp);
        void draw();
    private:
        Game& m_game;
        sf::Sprite m_h, m_t, m_u;
        int m_digits;
    };
}

#endif