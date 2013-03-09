#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <vector>
#include <utility>
#include <unordered_map>

namespace Joystick
{
    enum Axis
    {
        X, Y
    };

    enum Button
    {
        ButtonA, ButtonB,
        ButtonZ, ButtonY, ButtonX,
        TriggerLeft, TriggerRight,
        Other
    };

    class State
    {
        public:
            template <typename Iterator>
                State(unsigned int id, Iterator begin, Iterator end):
                    _id(id), _btnConfig(begin, end), _btnsUp()
            {
                _btnsUp[ButtonA] = false;
                _btnsUp[ButtonB] = false;
                _btnsUp[ButtonZ] = false;
                _btnsUp[ButtonY] = false;
                _btnsUp[TriggerLeft] = false;
                _btnsUp[TriggerRight] = false;
                _btnsUp[Other] = false;
            }

            State(unsigned int);
            State() = delete;
            State(State &&) = delete;
            State(const State &) = delete;
            ~State() = default;
            State & operator=(const State &);
            bool isConnected() const;
            bool isAxisFront(Axis) const;
            float axisPosition(Axis) const;
            bool isButtonFront(Button) const;
            bool isButtonUp(Button) const;
            bool isButtonDown(Button) const;

        private:
            std::vector<Button> _btnConfig;
            unsigned int _id;
            std::unordered_map<Button, bool> _btnsUp;
            std::pair<bool, bool> _axesUp;
    };

    class System
    {
        public:
            System();
            System(System &&) = delete;
            System(const System &) = delete;
            ~System();
            System & operator=(const System &);
            void init();
            void update();
            const State & state(unsigned int) const;

        private:
            std::unordered_map<unsigned int, State> _states;
    };
}

#endif
