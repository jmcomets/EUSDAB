#ifndef STATES_SHIELD_H_
#define STATES_SHIELD_H_

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Shield: public State
        {
            public:
                Shield(Shield &&) = default;
                Shield(const Shield &) = delete;
                Shield & operator=(const Shield &) = delete;

                Shield(Movement const &);
                virtual ~Shield();

                void onDown(const Event &);
                void onLeft(const Event &);
                void onRight(const Event &);

                void onTrigger(const Event &);

                void onNextFrame();

                void onEnter();
                void onLeave();

                void calcShieldValue();

                void changeImage();

                void setCurValue(unsigned int);
                void setMaxValue(unsigned int);
                void setNbrShieldstate(unsigned int);
                void setRegenSpeed(unsigned int);
                void setDecreaseSpeed(unsigned int);

            private:
                unsigned int _curValue;
                unsigned int _maxValue;
                unsigned int _nbrShieldstate;
                unsigned int _regenSpeed;
                unsigned int _decreaseSpeed;
                std::time_t _leaveTime;
        };
    }
}

#endif
