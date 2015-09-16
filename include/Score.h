#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>

namespace av {
    class Game;

    class Score {
    public:
        Score(Game& game, int bp);
        void setNew(bool isNew);
        void draw();
    private:
        Game& m_game;
        sf::Sprite m_h, m_t, m_u, m_l, m_r;
        bool m_isNew;
        int m_digits;
    };
}

#endif