#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

// Parent Game class
class Game {
 public:
  Game(){};

  virtual void Run(Controller const &controller, std::unique_ptr<Renderer> &renderer,std::size_t target_frame_duration) = 0;
  virtual int GetScore() const = 0;
  virtual int GetSize() const  = 0;
  virtual long GetHighestScore() const = 0;
 private:
};

//Child SnakeGame Class
class SnakeGame : public Game {
 public:
  SnakeGame(std::size_t grid_width, std::size_t grid_height);
  ~SnakeGame(){} //I. destructor

  void Run(Controller const &controller, std::unique_ptr<Renderer> &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;  //Get Current game score
  int GetSize() const;
  long GetHighestScore() const; //Gte Max score till now

 private:
  Snake snake;
  SDL_Point food;
  long g_highestScore;
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  int score{0};

  void PlaceFood();
  void Update();
};

#endif