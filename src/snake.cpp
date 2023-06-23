#include "snake.h"
#include <cmath>
#include <iostream>

 Snake::Snake(const Snake& other_snake) {
      if (this == &other_snake)
          return;

      this->updateGridWidth(other_snake.grid_width);
      this->updateGridHeight(other_snake.grid_height);
      this->direction = other_snake.direction;

      this->speed = other_snake.speed;
      this->size = other_snake.size;
      this->alive = other_snake.alive;
      this->head_x = other_snake.head_x;
      this->head_y = other_snake.head_y;

      for (int i=0; i<other_snake.body.size(); i++)
          this->body.push_back(other_snake.body[i]);
}

Snake& Snake::operator=(const Snake& other_snake) {
      if (this == &other_snake)
            return *this;

      this->updateGridWidth(other_snake.grid_width);
      this->updateGridHeight(other_snake.grid_height);
      this->direction = other_snake.direction;

      this->speed = other_snake.speed;
      this->size = other_snake.size;
      this->alive = other_snake.alive;
      this->head_x = other_snake.head_x;
      this->head_y = other_snake.head_y;
      for (int i=0; i<other_snake.body.size(); i++)
          this->body.push_back(other_snake.body[i]);

      return *this;
}
 Snake::Snake(Snake &&other_snake) {
      if (this == &other_snake)
          return;

      this->updateGridWidth(other_snake.grid_width);
      this->updateGridHeight(other_snake.grid_height);
      this->direction = other_snake.direction;

      this->speed = other_snake.speed;
      this->size = other_snake.size;
      this->alive = other_snake.alive;
      this->head_x = other_snake.head_x;
      this->head_y = other_snake.head_y;

      this->body.clear();
      for (int i=0; i<other_snake.body.size(); i++)
          this->body.push_back(other_snake.body[i]);

      other_snake.updateGridWidth(0);
      other_snake.updateGridHeight(0);
      other_snake.direction = Direction::kUp;
      other_snake.speed = 0;
      other_snake.size = 0;
      other_snake.alive = 0;
      other_snake.head_x = 0;
      other_snake.head_y = 0;
      other_snake.body.clear();
}

Snake& Snake::operator=(Snake &&other_snake) {
      if (this == &other_snake)
            return *this;

      this->updateGridWidth(other_snake.grid_width);
      this->updateGridHeight(other_snake.grid_height);
      this->direction = other_snake.direction;

      this->speed = other_snake.speed;
      this->size = other_snake.size;
      this->alive = other_snake.alive;
      this->head_x = other_snake.head_x;
      this->head_y = other_snake.head_y;
      for (int i=0; i<other_snake.body.size(); i++)
          this->body.push_back(other_snake.body[i]);

      other_snake.updateGridWidth(0);
      other_snake.updateGridHeight(0);
      other_snake.direction = Direction::kUp;
      other_snake.speed = 0;
      other_snake.size = 0;
      other_snake.alive = 0;
      other_snake.head_x = 0;
      other_snake.head_y = 0;
      other_snake.body.clear();
      return *this;
}

Snake::~Snake() {//I. destructor
     this->body.clear();
}

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.

  UpdateHead();

  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }
