#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "game_object.h"

class Snake : public GameObject
{
public:
  enum class Direction
  {
    kUp,
    kDown,
    kLeft,
    kRight
  };

  Snake(config::Configuration const &_config)
      : GameObject(
            ObjectType::snake,
            _config),
        pose({config.GridWidth / 2.0F, config.GridHeight / 2.0F})
  {
    body.push_back({static_cast<std::int32_t>(pose.x), static_cast<std::int32_t>(pose.y)});
  }

  void Update() override;

  void Render(SDL_Renderer *sdl_renderer) const override;

  bool IsCell(std::int32_t x, std::int32_t y) const override;

  void GrowBody();

  void UpdateIsDead();

  Direction direction = Direction::kUp;
  float speed{0.1F};

  std::int16_t size{1};
  SDL_FPoint pose{}; // pose is in grid blocks

private:
  void UpdatePose();
  void UpdateBody();
  bool CheckSelfCollide() const;

  bool growing{false};
};

#endif