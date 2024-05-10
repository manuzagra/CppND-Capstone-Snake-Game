#include "food.h"
#include <cmath>
#include <iostream>

void Food::Update() {}

// check if cell is occupied by the food.
bool Food::IsCell(std::int32_t x, std::int32_t y) const
{
  return (x == body.back().x && y == body.back().y);
}

void Food::SetPose(std::int32_t x, std::int32_t y)
{
  body.back().x = x;
  body.back().y = y;
}

void Food::Render(SDL_Renderer *sdl_renderer) const
{
  SDL_Rect block;
  block.w = config.ScreenWidth / config.GridWidth;
  block.h = config.ScreenHeight / config.GridHeight;

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = body.back().x * block.w;
  block.y = body.back().y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);
}