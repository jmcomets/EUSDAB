#ifndef GRAPHICS_SOUND_MANAGER_H_
#define GRAPHICS_SOUND_MANAGER_H_

#include <string>
#include <memory>
#include <map>
#include <SFML/Audio.hpp>

namespace EUSDAB
{
    namespace Graphics
    {
        class SoundManager
        {
            public:
                typedef std::shared_ptr<sf::SoundBuffer> SoundPtr;
                SoundManager(SoundManager &&) = delete;
                SoundManager(const SoundManager &) = delete;
                ~SoundManager() = default;
                SoundManager & operator=(const SoundManager &) = delete;

                static SoundPtr loadSound(const std::string &);

                static void playAsynchronous(SoundPtr const &);

            private:
                SoundManager();
                static SoundManager * instance();
                static std::shared_ptr<SoundManager> _instance;
                std::map<std::string, SoundPtr> _sounds;
        };
    }
}

#endif

