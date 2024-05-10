#ifndef FOOD_H
#define FOOD_H

#include <vector>
#include "SDL.h"
#include "game_object.h"

class Food : public GameObject
{
public:
  Food(config::Configuration const &_config, SDL_Point pose = {0, 0})
      : GameObject(
            ObjectType::food,
            _config)
  {
    body.push_back(pose);
  }

  void Update() override;

  void Render(SDL_Renderer *sdl_renderer) const override;

  bool IsCell(std::int32_t x, std::int32_t y) const override;

  void SetPose(std::int32_t x, std::int32_t y);
};

#endif