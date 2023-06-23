#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
    public:
        Controller();
        ~Controller();
        void HandleInput(int &running, Snake &snake) ;

    private:
        void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif