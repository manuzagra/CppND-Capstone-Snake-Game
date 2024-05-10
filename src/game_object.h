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
    GameObject(ObjectType _type, config::Configuration _config, bool _needed) : type(_type), config(_config), needed(_needed)
    {
    }
    GameObject(ObjectType _type, config::Configuration _config) : GameObject(_type, _config, false)
    {
    }
    virtual ~GameObject() = default;

    ObjectType Type() const { return type; }
    bool Alive() const { return alive; }
    void Alive(bool val) { alive = val; }
    bool Needed() const { return needed; }
    virtual void Update() = 0;
    virtual void Render(SDL_Renderer *sdl_renderer) const = 0;
    virtual bool IsCell(std::int32_t x, std::int32_t y) const = 0;
    bool Collide(GameObject const &other) const
    {
        for (auto const &part : body)
        {
            if (other.IsCell(part.x, part.y))
            {
                return true;
            }
        }
        return false;
    }

    std::vector<SDL_Point> body{};

protected:
    const ObjectType type{};
    const config::Configuration config{};
    bool alive{true};
    const bool needed{false};
};

#endif