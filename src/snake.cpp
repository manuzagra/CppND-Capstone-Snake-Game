#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  // We first capture the head's cell before updating.
  SDL_Point prev_cell{
      std::floor(pose.x),
      std::floor(pose.y)};
  UpdatePose();

  // Capture the head's cell after updating.
  SDL_Point current_cell{
      std::floor(pose.x),
      std::floor(pose.y)}; 

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(prev_cell);
  }
}

void Snake::UpdatePose() {
  switch (direction) {
    case Direction::kUp:
      pose.y -= speed;
      break;

    case Direction::kDown:
      pose.y += speed;
      break;

    case Direction::kLeft:
      pose.x -= speed;
      break;

    case Direction::kRight:
      pose.x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  pose.x = fmod(pose.x + config.GridWidth, config.GridWidth);
  pose.y = fmod(pose.y + config.GridHeight, config.GridHeight);
}

void Snake::UpdateBody(SDL_Point &prev_head_cell) {
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
  UpdateIsDead();
}

void Snake::Render(SDL_Renderer *sdl_renderer) const {
  SDL_Rect block;
  block.w = config.ScreenWidth / config.GridWidth;
  block.h = config.ScreenHeight / config.GridHeight;

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  auto const& head = body.back();
  block.x = head.x * block.w;
  block.y = head.y * block.h;
  if (alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);
}


void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::IsCell(std::int32_t x, std::int32_t y) const {
  if (x == static_cast<int>(pose.x) && y == static_cast<int>(pose.y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

// Check if the snake has died.
void Snake::UpdateIsDead(){
  for (auto const &item : body) {
    if (static_cast<int>(pose.x) == item.x && static_cast<int>(pose.y) == item.y) {
      alive = false;
    }
  }
}