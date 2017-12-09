#include "soundstereo.hpp"

SoundStereo::SoundStereo()
{
    leftBuffer_self = NULL;
    rightBuffer_self = NULL;
    leftBuffer = NULL;
    rightBuffer = NULL;
    leftChannel = new sf::Sound();
    rightChannel = new sf::Sound();
    leftChannel->setPosition(-1,0,0);
    rightChannel->setPosition(1,0,0);
}

SoundStereo::~SoundStereo()
{
    delete leftChannel;
    delete rightChannel;
    if(leftBuffer_self)
        delete leftBuffer_self;
    if(rightBuffer_self)
        delete rightBuffer_self;
}

bool SoundStereo::loadFromFile(const std::string& filename)
{
    std::vector<sf::SoundBuffer*> channels = loadFile(filename);
    if(channels.size() != 2)
        return false;
    if(leftBuffer_self)
        delete leftBuffer_self;
    if(rightBuffer_self)
        delete rightBuffer_self;
    leftBuffer_self = channels[0];
    rightBuffer_self = channels[1];
    setChannels(*leftBuffer_self, *rightBuffer_self);
    return true;
}

void SoundStereo::setChannels(const sf::SoundBuffer& left, const sf::SoundBuffer& right)
{
    leftBuffer = &left;
    rightBuffer = &right;
    leftChannel->setBuffer(*leftBuffer);
    rightChannel->setBuffer(*rightBuffer);
}

void SoundStereo::play()
{
    leftChannel->play();
    rightChannel->play();
}

void SoundStereo::pause()
{
    leftChannel->pause();
    rightChannel->pause();
}

void SoundStereo::stop()
{
    leftChannel->stop();
    rightChannel->stop();
}

void SoundStereo::setLoop(bool loop)
{
    leftChannel->setLoop(loop);
    rightChannel->setLoop(loop);
}

void SoundStereo::setPlayingOffset(sf::Time timeOffset)
{
    leftChannel->setPlayingOffset(timeOffset);
    rightChannel->setPlayingOffset(timeOffset);
}

bool SoundStereo::getLoop() const
{
    return rightChannel->getLoop();
}

sf::Time SoundStereo::getPlayingOffset() const
{
    return rightChannel->getPlayingOffset();
}

sf::SoundSource::Status SoundStereo::getStatus() const
{
    return rightChannel->getStatus();
}

void SoundStereo::setPitch(float pitch)
{
    leftChannel->setPitch(pitch);
    rightChannel->setPitch(pitch);
}

void SoundStereo::setVolume(float volume)
{
    leftChannel->setVolume(volume);
    rightChannel->setVolume(volume);
}

void SoundStereo::setPosition(float x, float y, float z)
{
    leftChannel->setPosition(x, y , z);
    rightChannel->setPosition(x, y , z);
}

void SoundStereo::setPositionRight(float x, float y, float z)
{
    rightChannel->setPosition(x, y , z);
}

void SoundStereo::setPositionLeft(float x, float y, float z)
{
    leftChannel->setPosition(x, y , z);
}

void SoundStereo::setPosition(const sf::Vector3f &position)
{
    leftChannel->setPosition(position);
    rightChannel->setPosition(position);
}

void SoundStereo::setPositionRight(const sf::Vector3f &position)
{
    rightChannel->setPosition(position);
}

void SoundStereo::setPositionLeft(const sf::Vector3f &position)
{
    leftChannel->setPosition(position);
}

void SoundStereo::setRelativeToListener(bool relative)
{
    leftChannel->setRelativeToListener(relative);
    rightChannel->setRelativeToListener(relative);
}

void SoundStereo::setMinDistance(float distance)
{
    leftChannel->setMinDistance(distance);
    rightChannel->setMinDistance(distance);
}

void SoundStereo::setAttenuation(float attenuation)
{
    leftChannel->setAttenuation(attenuation);
    rightChannel->setAttenuation(attenuation);
}

float SoundStereo::getPitch() const
{
    return rightChannel->getPitch();
}

float SoundStereo::getVolume() const
{
    return rightChannel->getVolume();
}

sf::Vector3f SoundStereo::getPositionRight() const
{
    return rightChannel->getPosition();
}

sf::Vector3f SoundStereo::getPositionLeft() const
{
    return leftChannel->getPosition();
}

bool SoundStereo::isRelativeToListener() const
{
    return rightChannel->isRelativeToListener();
}

float SoundStereo::getMinDistance() const
{
    return rightChannel->getMinDistance();
}

float SoundStereo::getAttenuation() const
{
    return rightChannel->getAttenuation();
}

std::vector<sf::SoundBuffer*> SoundStereo::loadFile(const std::string& filename)
{
    sf::SoundBuffer file;
    std::vector<sf::SoundBuffer*> result;
    if(!file.loadFromFile(filename))
        return result;
    result.push_back(new sf::SoundBuffer());
    result.push_back(new sf::SoundBuffer());

    const sf::Int16* buffer = file.getSamples();
    sf::Uint64 length = file.getSampleCount()/2;
    sf::Int16* left = new sf::Int16[length];
    sf::Int16* right = new sf::Int16[length];

    for(sf::Uint64 i = 0; i < length; ++i)
    {
        left[i] = *buffer++;
        right[i] = *buffer++;
    }

    result[0]->loadFromSamples(left, length, file.getChannelCount()/2, file.getSampleRate());
    result[1]->loadFromSamples(right, length, file.getChannelCount()/2, file.getSampleRate());

    delete [] left;
    delete [] right;

    return result;
}
