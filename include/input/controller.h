#ifndef INPUT_CONTROLLER_H_
#define INPUT_CONTROLLER_H_

namespace EUSDAB {
    namespace Input
    {
        class Controller
        {
            public:
                explicit Controller() = delete;
                explicit Controller(Controller const &) = delete;
                explicit Controller(Controller &&) = default;
                Controller & operator=(Controller const &) = delete;

                virtual ~Controller();
        };
    }
}

#endif

