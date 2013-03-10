#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <vector>
#include <utility>
#include <unordered_map>
#include <functional>

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
                init();
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
            unsigned int id() const;

        private:
            void init();
            std::vector<Button> _btnConfig;
            unsigned int _id;
            std::unordered_map<Button, bool, std::hash<int>> _btnsUp;
            std::pair<bool, bool> _axesUp;
    };
}

#endif
