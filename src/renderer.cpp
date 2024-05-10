#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(config::Configuration const& config)
    : screen_width(config.ScreenWidth),
      screen_height(config.ScreenHeight),
      grid_width(config.GridWidth),
      grid_height(config.GridHeight) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

  Renderer::Renderer(const Renderer &src) :
    sdl_window(src.sdl_window),
    sdl_renderer(src.sdl_renderer),
    grid_height(src.grid_height),
    grid_width(src.grid_width),
    screen_height(src.screen_height),
    screen_width(src.screen_width)
  {}

  Renderer::Renderer(Renderer &&src) noexcept :
    sdl_window(std::exchange(src.sdl_window, nullptr)),
    sdl_renderer(std::exchange(src.sdl_renderer, nullptr)),
    grid_height(std::exchange(src.grid_height, 0)),
    grid_width(std::exchange(src.grid_width, 0)),
    screen_height(std::exchange(src.screen_height, 0)),
    screen_width(std::exchange(src.screen_width, 0))
  {}

  Renderer& Renderer::operator=(const Renderer &src) {
    if (this == &src)
      return *this;

    sdl_window = src.sdl_window;
    sdl_renderer = src.sdl_renderer;
    grid_height = src.grid_height;
    grid_width = src.grid_width;
    screen_height = src.screen_height;
    screen_width = src.screen_width;

    return *this;
  }

  Renderer& Renderer::operator=(Renderer&& src) noexcept {
    if (this != &src) {
      SDL_DestroyWindow(sdl_window);
      SDL_DestroyRenderer(sdl_renderer);
    }

    sdl_window = src.sdl_window;
    sdl_renderer = src.sdl_renderer;
    grid_height = src.grid_height;
    grid_width = src.grid_width;
    screen_height = src.screen_height;
    screen_width = src.screen_width;

    src.sdl_window = nullptr;
    src.sdl_renderer = nullptr;
    src.grid_height = 0;
    src.grid_width = 0;
    src.screen_height = 0;
    src.screen_width = 0;

    return *this;
  }

void Renderer::Render(std::vector<std::shared_ptr<GameObject>>& objects) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render objects
  for(auto const& obj: objects){
    obj->Render(sdl_renderer);
  }
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
