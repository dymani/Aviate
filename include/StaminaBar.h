#ifndef STAMINA_BAR_H
#define STAMINA_BAR_H

#include <SFML/Graphics.hpp>

namespace av {
    class Game;
    class Player;

    class StaminaBar {
    public:
        StaminaBar(Game& game, Player& player);
        bool update();
        void draw();
        void end();
    private:
        Game& m_game;
        Player& m_player;
        int m_stamina, m_hp;
        sf::Sprite m_base, m_bar, m_top, m_cover;
        bool m_end;
    };
}

#endif