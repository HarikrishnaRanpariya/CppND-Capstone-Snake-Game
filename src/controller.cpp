#include "controller.h"
#include <iostream>
#include <mutex>
#include <unistd.h>
#include <condition_variable>
#include "SDL.h"
#include "snake.h"

extern std::mutex s_mutex, mtx;
extern std::condition_variable cv;


Controller::Controller()
{
  std::cout <<"Cmdline Guide: SnakeGame:\n";
  std::cout <<"    'a' for Pause\n";
  std::cout <<"    'q' for Resume\n";
  std::cout <<"    'Pgup' for Up direction\n";
  std::cout <<"    'PgDn' for Down direction\n";
  std::cout <<"    'Home' for Left direction\n";
  std::cout <<"    'End' for Right direction\n\n";
}

Controller::~Controller()
{
  //TODO
}

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(int &running, Snake &snake)  {
  SDL_Event e;

  while (1) { // Infinite loop
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        running = 2;
        break;
      }
      else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
         case SDLK_a:
            running = 1;
            break;

         case SDLK_q:
            running = 0;
            cv.notify_all();
            break;

          case SDLK_UP:
            s_mutex.lock();
            ChangeDirection(snake, Snake::Direction::kUp,
                            Snake::Direction::kDown);
            s_mutex.unlock();
            break;

          case SDLK_DOWN:
            s_mutex.lock();
            ChangeDirection(snake, Snake::Direction::kDown,
                            Snake::Direction::kUp);
            s_mutex.unlock();
            break;

          case SDLK_LEFT:
            s_mutex.lock();
            ChangeDirection(snake, Snake::Direction::kLeft,
                            Snake::Direction::kRight);
            s_mutex.unlock();
            break;

          case SDLK_RIGHT:
            s_mutex.lock();
            ChangeDirection(snake, Snake::Direction::kRight,
                            Snake::Direction::kLeft);
            s_mutex.unlock();
            break;

          default:
            std::cout <<"Pressed Invalid Key...\n";
            std::cout <<"Cmdline Guide: SnakeGame:\n";
            std::cout <<"    'a' for Pause\n";
            std::cout <<"    'q' for Resume\n";
            std::cout <<"    'Pgup' for Up direction\n";
            std::cout <<"    'PgDn' for Down direction\n";
            std::cout <<"    'Home' for Left direction\n";
            std::cout <<"    'End' for Right direction\n\n";

            break;
        }
      }
    }

    // User user request for Quit the Game.
    if (running == 2) break;

    usleep(1000);
  }
}
