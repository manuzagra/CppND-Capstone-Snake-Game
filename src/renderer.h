#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "configuration.h"
#include "game_object.h"

class Renderer
{
public:
  Renderer(config::Configuration const &config);
  ~Renderer();

  Renderer(const Renderer &src);
  Renderer(Renderer &&src) noexcept;

  Renderer &operator=(const Renderer &src);
  Renderer &operator=(Renderer &&src) noexcept;

  void Render(std::vector<std::shared_ptr<GameObject>> &objects);
  void UpdateWindowTitle(int score, int fps);

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  std::size_t screen_width;
  std::size_t screen_height;
  std::size_t grid_width;
  std::size_t grid_height;
};

#endif