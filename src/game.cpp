#include "game.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <condition_variable>
#include "SDL.h"

using namespace std;

mutex s_mutex, mtx;
condition_variable cv;

SnakeGame::SnakeGame(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
  string s_highestScore = "";
  ifstream f_highscore("HighestScore.txt");
  getline(f_highscore, s_highestScore);
  f_highscore.close();
  if(s_highestScore == "") {
    g_highestScore = 0;
  }
  else {
    g_highestScore = stoi(s_highestScore);
  }
}

long SnakeGame::GetHighestScore() const { return g_highestScore;}

void SnakeGame::Run(Controller const &controller, unique_ptr<Renderer> &renderer,
               std::size_t target_frame_duration) {

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  int running = 0;

  //Create Thread to handle user input
  thread cntlr_thread(&Controller::HandleInput, controller, ref(running), ref(snake));
  //Detach thread from its parent
  cntlr_thread.detach();

  while (running != 2) {
    unique_lock<mutex> readLock(mtx);
    while ( running == 1 ) cv.wait(readLock);

    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    Update();
    s_mutex.lock();
    renderer->Render(snake, food);
    s_mutex.unlock();
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer->UpdateWindowTitle(score, frame_count, g_highestScore);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }

    // Added 1 ms time delay
    usleep(1000);
  }

}

void SnakeGame::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (! snake.SnakeCell<int>(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void SnakeGame::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    if (g_highestScore < score) {
        g_highestScore = score;
        //Update Hightest score value in a file
        ofstream t_highScore("HighestScore.txt");
        t_highScore<<g_highestScore;
        t_highScore.close();
    }
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int SnakeGame::GetScore() const { return score; }
int SnakeGame::GetSize() const { return snake.size; }