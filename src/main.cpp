#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "configuration_helper.h"

int main() {

  config::Configuration configuration{};
  try
  {
    configuration = config::parse(config::default_configuration_file_path);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    std::cout << "Using default configuration!" << "\n";
  }
  
  Renderer renderer(configuration);
  Controller controller;
  Game game(configuration);
  game.Run(controller, renderer, configuration.MsPerFrame());
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}