#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <cstdint>
#include "SDL.h"
#include "configuration.h"

enum class ObjectType
{
    snake,
    food,
    obstacle
};

class GameObject
{
public:
    GameObject(ObjectType _type, config::Configuration _config, bool _needed = false) : type(_type), config(_config), needed(_needed)
    {
    }

    ObjectType Type() const
    {
        return type;
    }
    virtual void Update() = 0;
    virtual void Render(SDL_Renderer *sdl_renderer) const = 0;
    virtual bool IsCell(std::int32_t x, std::int32_t y) const = 0;
    bool Collide(GameObject const &other) const
    {
        // for (auto const &part : body)
        // {
        //     if (other.IsCell(part.x, part.y))
        //     {
        //         return true;
        //     }
        // }
        return false;
    }

    ObjectType type{};

    std::vector<SDL_Point> body{};

    bool alive{true};
    bool needed{false};

    config::Configuration config{};
};

#endif