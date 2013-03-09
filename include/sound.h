#ifndef SOUND_H_
#define SOUND_H_

class Sound
{
    public:
        Sound();
        Sound(Sound &&);
        Sound(const Sound &);
        ~Sound();
        Sound & operator=(const Sound &);
};

#endif
