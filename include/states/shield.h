#ifndef STATES_SHIELD_H
#define STATES_SHIELD_H

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

                Shield();
                virtual ~Shield();

                void onUp(const Event &);
                void onDown(const Event &);
                void onLeft(const Event &);
                void onRight(const Event &);

                void onA(const Event &);
                void onB(const Event &);
                //void onX(const Event &);
                //void onY(const Event &);
                //void onZ(const Event &);
                void onTrigger(const Event &);

                void onNextFrame();

                //void onAttack(const Event &);
                //void onDamage(const Event &);

                //void onGround(const Event &);

                void onEnter();
                void onLeave();
                
                void calcShieldValue();
                
                void changeImage();
                
                private:
                
                unsigned int _curValue;
                unsigned int _maxValue;
                unsigned int _nbrShieldstate;
                float _regenSpeed;
                float _decreaseSpeed;
                std::time_t _leaveTime;
        };
    }
}

#endif


