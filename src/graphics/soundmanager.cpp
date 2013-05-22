#include <graphics/soundmanager.h>
#include <stdexcept>
#include <thread>

namespace EUSDAB
{
    namespace Graphics
    {
        std::shared_ptr<SoundManager> SoundManager::_instance(nullptr);

        SoundManager::SoundManager():
            _sounds()
        {
        }

        SoundManager * SoundManager::instance()
        {
            if (_instance.get() == nullptr)
            {
                _instance.reset(new SoundManager());
            }

            return _instance.get();
        }

        SoundManager::SoundPtr SoundManager::loadSound(
                const std::string & filename)
        {
            SoundManager * inst = instance();
            auto it = inst->_sounds.find(filename);
            if(it == inst->_sounds.end()) // New sound
            {
                sf::SoundBuffer * tx = new sf::SoundBuffer();
                if(tx->loadFromFile(filename))
                {
                    SoundPtr ptr(tx);
                    inst->_sounds.insert(std::make_pair(filename, ptr));
                    return ptr;
                }
                else
                {
                    throw std::runtime_error("Sound couldn't be loaded");
                }
            }
            else
            {
                return it->second;
            }
        }

        void SoundManager::playAsynchronous(SoundPtr const & s)
        {
            static auto f_play = [](SoundManager::SoundPtr const & s)
            {
                sf::Sound sound(*s);
                sound.play();
                while(sound.getStatus() == sf::Sound::Playing) {
                    std::this_thread::sleep_for(
                            std::chrono::milliseconds(100));
                }
            };

            std::thread t(f_play, std::ref(s));
            t.detach();
        }
    }
}

