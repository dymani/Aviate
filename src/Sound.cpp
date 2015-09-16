#include "Sound.h"

namespace av {
    Sound::Sound() {
    }

    void Sound::setBuffer(sf::SoundBuffer& sound) {
        m_buffer = sound;
    }

    void Sound::play(bool loop) {
        m_sound.setBuffer(m_buffer);
        m_sound.setLoop(loop);
        m_sound.play();
    }

    void Sound::stop() {
        m_sound.stop();
    }
}