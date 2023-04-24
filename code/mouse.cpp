#include "Mouse.hpp"

Mouse::Mouse()
{
    SDL_GetMouseState(&x, &y);
}

int Mouse::getX()
{
    SDL_GetMouseState(&x, &y);
    return x;
}

int Mouse::getY()
{
    SDL_GetMouseState(&x, &y);
    return y;
}

Vector2f Mouse::getPos()
{
    SDL_GetMouseState(&x, &y);
    return Vector2f(x, y);
}

bool Mouse::isInsideEntity(Entity& entity)
{
    Vector2f currentPos = getPos();
    return
    (currentPos.x >= entity.getPosition().x && currentPos.x <= entity.getPosition().x + entity.getWidth()
    && currentPos.y >= entity.getPosition().y && currentPos.y <= entity.getPosition().y + entity.getHeight());
}