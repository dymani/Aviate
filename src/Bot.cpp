#include "Bot.h"
#include "Game.h"

namespace av {
    Bot::Bot(Game& game):m_game(game) {
        m_coord = {32, 0};
        m_sprite.setTexture(game.getTexture("sprite"));
        m_sprite.setTextureRect({9, 0, 9, 9});
        m_sprite.setScale({6.0F, 6.0F});
        m_sprite.setPosition(float(m_coord.x - 4.5F) * 6, 492.0F);
        m_direction = LEFT;
        m_left = true;
        m_frame = 1;
        m_tickToFrame = 0;
    }

    void Bot::update() {
        m_tickToFrame++;
        if(m_tickToFrame > 10) {
            m_tickToFrame = 0;
            m_frame = m_frame == 3?0:m_frame + 1;
        }
        if(m_finishingTicks <= 0) {
            m_direction = Direction(rand() % 3);
            m_finishingTicks = rand() % 100 + 100;
            if(m_direction == IDLE)m_finishingTicks *= 3;
        } else {
            switch(m_direction) {
                case LEFT:
                    m_left = true;
                    m_coord.x -= 0.2F;
                    m_finishingTicks -= 1;
                    if(m_coord.x <= 0) {
                        m_coord.x = 0;
                        m_direction = RIGHT;
                    }
                    break;
                case RIGHT:
                    m_left = false;
                    m_coord.x += 0.2F;
                    m_finishingTicks -= 1;
                    if(m_coord.x >= 64) {
                        m_coord.x = 64;
                        m_direction = LEFT;
                    }
                    break;
                case IDLE:
                    m_finishingTicks -= 1;
                    m_frame = 1;
                    break;
            }
        }
    }

    void Bot::draw() {
        m_sprite.setTextureRect({m_frame == 3?9:m_frame * 9, !m_left * 9, 9, 9});
        m_sprite.setPosition(float(int((m_coord.x - 4.5) * 6)), 492.0F);
        m_game.getWindow().draw(m_sprite);
    }
}