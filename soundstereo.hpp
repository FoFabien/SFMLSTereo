#ifndef SOUNDSTEREO_HPP
#define SOUNDSTEREO_HPP

#include <vector>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class SoundStereo
{
    public:
        SoundStereo();
        ~SoundStereo();
        bool loadFromFile(const std::string& filename);
        void setChannels(const sf::SoundBuffer& left, const sf::SoundBuffer& right);

        void play();
        void pause();
        void stop();
        void setLoop(bool loop);
        void setPlayingOffset(sf::Time timeOffset);
        bool getLoop() const;
        sf::Time getPlayingOffset() const;
        sf::SoundSource::Status getStatus() const;
        void setPitch(float pitch);
        void setVolume(float volume);
        void setPosition(float x, float y, float z);
        void setPositionRight(float x, float y, float z);
        void setPositionLeft(float x, float y, float z);
        void setPosition(const sf::Vector3f &position);
        void setPositionRight(const sf::Vector3f &position);
        void setPositionLeft(const sf::Vector3f &position);
        void setRelativeToListener(bool relative);
        void setMinDistance(float distance);
        void setAttenuation(float attenuation);
        float getPitch() const;
        float getVolume() const;
        sf::Vector3f getPositionRight() const;
        sf::Vector3f getPositionLeft() const;
        bool isRelativeToListener() const;
        float getMinDistance() const;
        float getAttenuation() const;

        static std::vector<sf::SoundBuffer*> loadFile(const std::string& filename);
    protected:
        sf::SoundBuffer* leftBuffer_self;
        sf::SoundBuffer* rightBuffer_self;
        const sf::SoundBuffer* leftBuffer;
        const sf::SoundBuffer* rightBuffer;
        sf::Sound* leftChannel;
        sf::Sound* rightChannel;
};

#endif // SOUNDSTEREO_HPP
