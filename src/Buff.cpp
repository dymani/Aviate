#include "Buff.h"
#include "Game.h"
#include "Player.h"

namespace av {
    Buff::Buff(Game& game, Player& player, sf::Vector2i coord, int type): m_game(game), m_player(player) {
        m_coord = coord;
        m_type = TYPE(type);
        m_sprite.setTexture(m_game.getTexture("gui"));
        switch(m_type) {
            case BP:
                m_sprite.setTextureRect({40, 68, 5, 7});
                m_sprite.setOrigin(2.5, 3.5);
                break;
            case LVL:
                m_sprite.setTextureRect({46, 68, 7, 7});
                m_sprite.setOrigin(3.5, 3.5);
                break;
            case STM:
                m_sprite.setTextureRect({56, 70, 3, 3});
                m_sprite.setOrigin(1.5, 1.5);;
                break;
        }
        m_sprite.setPosition(float(int(m_coord.x * 6)), float(int((82 - m_coord.y) * 6)));
        m_sprite.setScale(6.0F, 6.0F);
    }

    void Buff::draw() {
        m_game.getWindow().draw(m_sprite);
    }

    void Buff::collect() {
        switch(m_type) {
            case BP:
                m_player.setBp(m_player.getBp() + int(1 * m_player.getLevelSpeed() * m_player.getLevelSpeed()));
                break;
            case LVL:
                m_player.setLevel(m_player.getLevel() + 1);
                break;
            case STM:
                m_player.setStamina(m_player.getStamina() + int(400 * m_player.getLevelSpeed()));
                break;
        }
    }

    sf::Vector2i Buff::getCoord() {
        return m_coord;
    }

    sf::FloatRect Buff::getCollisionBox() {
        switch(m_type) {
            case BP:
                return{m_coord.x - 2.5F, m_coord.y + 3.5F, 5, 7};
            case LVL:
                return{m_coord.x - 3.5F, m_coord.y + 3.5F, 7, 7};
            case STM:
                return{m_coord.x - 1.5F, m_coord.y + 1.5F, 3, 3};
        }
        return{0, 0, 0, 0};
    }
}