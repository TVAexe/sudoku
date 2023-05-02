#pragma once
#include<SDL.h>
#include<SDL_image.h>

#include "Vector2f.hpp"

class Entity
{
    public:
        Entity(Vector2f pos, float pWidth, float pHeight, SDL_Texture* tex);
        Vector2f& getPosition();
        SDL_Texture* getTexture();
        SDL_Rect getCurrentFrame();
        float getWidth();
        float getHeight();
        void setPosition(float pX, float pY);
        void setWidth(float pWidth);
        void setHeight(float pHeight);
    protected:
        Vector2f position;
        SDL_Rect currentFrame;
        SDL_Texture* texture;
        float width, height;
};