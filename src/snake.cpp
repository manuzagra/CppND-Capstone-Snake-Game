#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  if(alive){
    UpdatePose();
    UpdateBody();
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

void Snake::UpdateBody() {

  // the cell of the pose
  SDL_Point pose_cell{
      std::floor(pose.x),
      std::floor(pose.y)};

  // the cell of the head
  SDL_Point head_cell{
      body.back().x,
      body.back().y}; 

  // check it the pose has moved to a new cell and update the body
  if (head_cell.x != pose_cell.x || head_cell.y != pose_cell.y){
    // Add previous head location to vector
    body.push_back(pose_cell);

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

}

void Snake::GrowBody() { growing = true; }

// check if cell is occupied by snake.
bool Snake::IsCell(std::int32_t x, std::int32_t y) const {
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

bool Snake::CheckSelfCollide() const {
  auto const& head = body.back();
  for(std::int32_t i = 0; i < body.size()-1; i++){
    if ((static_cast<int>(head.x) == body[i].x && static_cast<int>(head.y) == body[i].y)) {
      return false;
    }
  }
  return true;
}

// Check if the snake has died.
void Snake::UpdateIsDead(){
  alive = CheckSelfCollide();
}

void Snake::Render(SDL_Renderer *sdl_renderer) const {
  SDL_Rect block;
  block.w = config.ScreenWidth / config.GridWidth;
  block.h = config.ScreenHeight / config.GridHeight;

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (auto const &point : body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;

    // check if it is the head and change the color
    if (&point == &body.back()){
      if (alive) {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
      } else {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
      }
    }
    SDL_RenderFillRect(sdl_renderer, &block);
  }

}