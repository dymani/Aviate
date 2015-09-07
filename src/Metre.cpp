#include "Metre.h"
#include "Game.h"
#include "Player.h"

namespace av {
    Metre::Metre(Game& game, Player& player): m_game(game), m_player(player) {
        m_metre.setTexture(m_game.getTexture("gui"));
        m_metre.setTextureRect({63, 49, 4, 29});
        m_metre.setScale(6, 6);
        m_metre.setPosition({348, 96});
        m_icon.setTexture(m_game.getTexture("gui"));
        m_icon.setTextureRect({68, 51, 4, 4});
        m_icon.setScale(6, 6);
        m_icon.setPosition({348, 252});
    }

    void Metre::update() {
        m_height = m_player.getCoord().y;
        m_icon.setPosition({348, float(252 - m_height / 20)});
    }

    void Metre::draw() {
        m_game.getWindow().draw(m_metre);
        m_game.getWindow().draw(m_icon);
    }
}