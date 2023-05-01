#pragma once

#include<SDL.h>
#include<SDL_image.h>

#include "code/Vector2f.hpp"
#include "code/Square.hpp"


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
