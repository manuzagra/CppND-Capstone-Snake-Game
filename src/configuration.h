#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <cstdint>

namespace config
{

  struct Configuration
  {
    std::int16_t FramesPerSecond{60};
    std::int32_t ScreenWidth{640};
    std::int32_t ScreenHeight{640};
    std::int16_t GridWidth{32};
    std::int16_t GridHeight{32};


    std::int16_t MsPerFrame(){return 1000 / FramesPerSecond;}
  };

}

#endif