#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Audio/Listener.hpp>
#include "soundstereo.hpp"

int main()
{
    std::cout << "Hello world!" << std::endl;
    SoundStereo stereo;
    if(stereo.loadFromFile("stereo.wav"))
    {
        std::cout << "Playing stereo.wav" << std::endl;

        // to change the listener position and orientation in the 3D space:
        //sf::Listener::setPosition(10.f, 0.f, 5.f);
        //sf::Listener::setDirection(1.f, 0.f, 0.f);

        // Spatialization
        stereo.setRelativeToListener(true);
        stereo.setPositionRight(1,1,0); // right, slightly over the listener
        stereo.setPositionLeft(-1,-1,0); // left, slightly under the listener

        // loop and play for a short while
        stereo.setLoop(true);
        stereo.play();
        sf::sleep(sf::seconds(4));
        stereo.stop();
    }
    return 0;
}
