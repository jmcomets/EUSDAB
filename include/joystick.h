#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <cstddef>
#include <algorithm>
#include <bitset>
#include <list>
#include <utility>
#include <array>
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

    // Number of real joysticks handled
    constexpr unsigned int NbButtons = 32;

    // Number of real buttons handled
    constexpr unsigned int NbJoysticks = 8;

    class ButtonConfig
    {
        public:
            ButtonConfig();
            template <typename Iterator>
                ButtonConfig(Iterator begin, Iterator end):
                    _btnConfig()
            {
                std::copy(begin, end, _btnConfig.begin());
            }

            ButtonConfig(ButtonConfig &&) = default;
            ButtonConfig(const ButtonConfig &) = default;
            ~ButtonConfig() = default;
            ButtonConfig & operator=(const ButtonConfig &) = default;
            unsigned int operator[](Button) const;

        private:
            std::array<Button, NbButtons> _btnConfig;
    };

    struct Mask
    {
        Mask();
        Mask(const Mask &) = default;
        Mask(Mask &&) = default;
        ~Mask() = default;
        Mask & operator=(const Mask &) = default;
        bool operator==(const Mask &) const;
        std::bitset<NbButtons> buttons;
        bool axisX, axisY;
    };

    class State
    {
        public:
            // Construct with default config
            State(unsigned int);

            // Construct with inplace config
            template <typename Iterator>
                State(unsigned int id, Iterator begin, Iterator end):
                    _id(id), _frameMasks(),
                    _btnConfig(begin, end) {}

            // Construct with config
            State(unsigned int id, const ButtonConfig & config):
                _id(id), _frameMasks(),
                _btnConfig(config) {}

            State() = delete;
            State(State &&) = delete;
            State(const State &) = delete;
            ~State() = default;
            State & operator=(const State &) = delete;

            // Joystick connected
            bool isConnected() const;

            // Status for current frame
            bool isButtonUp(Button) const;
            bool isButtonDown(Button) const;
            float axisPosition(Axis) const;

            // Event mask for current frame
            bool isAxisFront(Axis) const;
            bool isButtonFront(Button) const;
            bool isMask(const Mask &) const;

            // Event mask during a frame interval
            bool isAxisFront(Axis, unsigned int) const;
            bool isButtonFront(Button, unsigned int) const;
            bool isMask(const Mask &, unsigned int) const;

            // Update the handled event mask
            void update();

            // Handled joystick's id
            unsigned int id() const;

        private:
            unsigned int _id;
            std::list<Mask> _frameMasks;
            ButtonConfig _btnConfig;
    };

    // Update entire joystick system
    void update();
}

#endif
