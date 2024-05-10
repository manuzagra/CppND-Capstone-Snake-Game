#ifndef CONFIGURATION_HELPER_H
#define CONFIGURATION_HELPER_H

#include "configuration.h"

#include <fstream>
#include <sstream>

namespace config
{

    constexpr char default_configuration_file_path[]{"./config.txt"};

    Configuration parse(std::string path)
    {
        Configuration config{};

        std::string line;
        std::ifstream filestream(path);

        if (filestream.is_open())
        {

            std::getline(filestream, line);

            std::istringstream linestream(line);

            linestream >> config.FramesPerSecond >> config.ScreenWidth >> config.ScreenHeight >> config.GridWidth >> config.GridHeight;

            auto ScreenWidth = (config.ScreenWidth / config.GridWidth) * config.GridWidth;
            auto ScreenHeight = (config.ScreenHeight / config.GridHeight) * config.GridHeight;

            if (config.ScreenWidth != ScreenWidth || config.ScreenHeight != ScreenHeight){
                std::cout << "Adjusting screen resolution to " << ScreenWidth << "x" << ScreenHeight << "\n";
                config.ScreenWidth = ScreenWidth;
                config.ScreenHeight = ScreenHeight;
            }
        }
        else
        {
            throw std::runtime_error("Configuration file " + path + " does not exist!");
        }

        return config;
    }

}

#endif