#include <soundmanager.h>
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
                //sf::SoundBuffer * tx = new sf::SoundBuffer();
                sf::Music * tx = new sf::Music();
                tx->setVolume(100);
                //if(tx->loadFromFile(filename))
                if(tx->openFromFile(filename))
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
            auto f_play = [](SoundPtr const & s)
            {
                s->play();
                //sf::Sound sound(s);
                //sound.play();
                while(s->getStatus() == sf::Sound::Playing) {
                    std::this_thread::sleep_for(
                            std::chrono::milliseconds(100));
                }
            };

            s->play();
            //std::thread t(f_play, std::ref(s));
            //t.detach();
        }
    }
}

