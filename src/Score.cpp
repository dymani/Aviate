#include "Score.h"
#include "Game.h"

namespace av {
    Score::Score(Game& game, int bp):m_game(game) {
        int u = bp % 10;
        int t = int(bp % 100 - u) / 10;
        int h = int((bp - t * 10 - u) / 100);
        m_digits = 0;
        if(h > 0) {
            m_h.setTexture(m_game.getTexture("gui"));
            m_h.setTextureRect({6 * h, 88, 6, 8});
            m_h.setScale(6.0F, 6.0F);
            m_digits += 1;
        }
        if(t > 0 || h > 0) {
            m_t.setTexture(m_game.getTexture("gui"));
            m_t.setTextureRect({6 * t, 88, 6, 8});
            m_t.setScale(6.0F, 6.0F);
            m_digits += 1;
        }
        m_u.setTexture(m_game.getTexture("gui"));
        m_u.setTextureRect({6 * u, 88, 6, 8});
        m_u.setScale(6.0F, 6.0F);
        m_digits += 1;
        m_l.setTexture(m_game.getTexture("gui"));
        m_l.setTextureRect({60, 88, 6, 8});
        m_l.setScale(6.0F, 6.0F);
        m_r.setTexture(m_game.getTexture("gui"));
        m_r.setTextureRect({66, 88, 6, 8});
        m_r.setScale(6.0F, 6.0F);
        switch(m_digits) {
            case 3:
                m_l.setPosition(102, 276);
                m_h.setPosition(138, 276);
                m_t.setPosition(174, 276);
                m_u.setPosition(210, 276);
                m_r.setPosition(246, 276);
                break;
            case 2:
                m_l.setPosition(120, 276);
                m_t.setPosition(156, 276);
                m_u.setPosition(192, 276);
                m_r.setPosition(228, 276);
                break;
            case 1:
                m_l.setPosition(138, 276);
                m_u.setPosition(174, 276);
                m_r.setPosition(210, 276);
                break;
        }
    }

    void Score::setNew(bool isNew) {
        m_isNew = isNew;
    }

    void Score::draw() {
        switch(m_digits) {
            case 3:
                m_game.getWindow().draw(m_h);
            case 2:
                m_game.getWindow().draw(m_t);
            case 1:
                m_game.getWindow().draw(m_u);
                break;
        }
        if(m_isNew) {
            m_game.getWindow().draw(m_l);
            m_game.getWindow().draw(m_r);
        }
    }
}