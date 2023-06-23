#include <iostream>
#include <memory>
#include <fstream>

#include "controller.h"
#include "game.h"
#include "renderer.h"

using namespace std;
int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  std::unique_ptr<Renderer> renderer(new Renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight));
  Controller controller;
  Game *game;
  SnakeGame s_game(kGridWidth, kGridHeight);
  game = &s_game;

  game->Run(controller, renderer, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  std::cout << "\n======================================\n";
  std::cout << "Score: " << game->GetScore() << "\n";
  std::cout << "Size: " << game->GetSize() << "\n";
  std::cout << "Highest Score: " << game->GetHighestScore() << "\n";
  return 0;
}