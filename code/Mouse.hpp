#pragma once

#include<SDL.h>
#include<SDL_image.h>

#include "Vector2f.hpp"
#include "Square.hpp"


class Mouse
{
public:
    Mouse();
    int getX();
    int getY();
    Vector2f getPos();
    bool isInsideEntity(Entity& entity);
private:
    int x, y;
};
