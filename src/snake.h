#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>
#include "SDL.h"


class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}
  Snake(const Snake& other_snake);// I. Copy Constructor
  Snake& operator=(const Snake& other_snake);// II. Copy Assignment Constructor
  Snake(Snake &&other_snake);// III. Move Constructor
  Snake& operator=(Snake &&other_snake);// IV. Move Assignment Constructor
  ~Snake();// V. Destructor

  void Update();
  void GrowBody();

  template <typename T>
  bool SnakeCell(T x, T y) {
    if (x == static_cast<T>(head_x) && y == static_cast<T>(head_y)) {
      return true;
    }
    for (auto const &item : body) {
      if (x == item.x && y == item.y) {
        return true;
      }
    }
    return false;
  }

  void updateGridWidth(int width) {grid_width = width;}
  void updateGridHeight(int height) {grid_height = height;}
  int getGridWidth(void) {return grid_width;}
  int getGridHeight(void) {return grid_height;}

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

  private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif