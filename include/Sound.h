#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>

namespace av {
    class Sound {
    public:
        Sound();
        void setBuffer(sf::SoundBuffer& sound);
        void play(bool loop = false);
        void stop();
    private:
        sf::SoundBuffer m_buffer;
        sf::Sound m_sound;
    };
}

#endif