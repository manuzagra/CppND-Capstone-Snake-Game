#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include <mutex>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "food.h"
#include "configuration.h"

class Game
{
public:
  Game(config::Configuration config);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

private:
  std::shared_ptr<Snake> snake;
  std::shared_ptr<Food> food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int frame_count{0};
  bool running{true};

  void PlaceFood();
  void Update();
  void UpdateWindowTitle(Renderer &renderer);

  std::mutex renderer_mutex;
};

#endif