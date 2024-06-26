#include "game.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "SDL.h"

Game::Game(config::Configuration config) // Game(std::size_t grid_width, std::size_t grid_height)
    : snake(std::make_shared<Snake>(config)),
      food(std::make_shared<Food>(config)),
      engine(dev()),
      random_w(0, static_cast<int>(config.GridWidth - 1)),
      random_h(0, static_cast<int>(config.GridHeight - 1))
{
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;

  std::thread t(&Game::UpdateWindowTitle, this, std::ref(renderer));

  std::vector<std::shared_ptr<GameObject>> objects{snake, food};

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, *snake);
    Update();
    {
      const std::lock_guard<std::mutex> lock(renderer_mutex);
      renderer.Render(objects);
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  t.join();
}

void Game::UpdateWindowTitle(Renderer &renderer)
{
  while (running)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    const std::lock_guard<std::mutex> lock(renderer_mutex);
    renderer.UpdateWindowTitle(score, frame_count);
    frame_count = 0;
  }
}

void Game::PlaceFood()
{
  int x, y;
  while (true)
  {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake->IsCell(x, y))
    {
      food->SetPose(x, y);
      return;
    }
  }
}

void Game::Update()
{
  if (!snake->Alive())
    return;

  snake->Update();

  int new_x = static_cast<int>(snake->pose.x);
  int new_y = static_cast<int>(snake->pose.y);

  // Check if there's food over here
  if (food->IsCell(new_x, new_y))
  {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake->GrowBody();
    snake->speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->size; }