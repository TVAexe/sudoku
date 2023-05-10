#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<fstream>
#include<string>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Square.hpp"
#include "Board.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(window == NULL) std::cout << "[ERROR] NULL Window: " << SDL_GetError() << std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    windowHeight = height;
    windowWidth = width; 
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filePath);
    if(texture == NULL) std::cout << "[ERROR] Texture Load Failed: " << SDL_GetError() << std::endl;
    return texture;
}

void RenderWindow::loadTextures(const char* filePath, std::vector<SDL_Texture*>& o_list)
{
    std::ifstream list(filePath);
    std::string currentTexture;
    while(std::getline(list, currentTexture))
    {
        o_list.push_back(loadTexture(currentTexture.c_str()));
    }
}

int RenderWindow::getRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex(window);
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex, 0, &mode);
    return mode.refresh_rate;
}

int RenderWindow::getWidth()
{
    return windowWidth;
}

int RenderWindow::getHeight()
{
    return windowHeight;
}

void RenderWindow::updateSize()
{
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
}

void RenderWindow::clean()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::clearScreen()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::renderBox(Vector2f position, float width, float height)
{
    SDL_Rect dest;
    dest.x = position.x;
    dest.y = position.y;
    dest.w = width;
    dest.h = height;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &dest);
    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
}

void RenderWindow::render(Entity& entity)
{
    SDL_Rect src;
    src.x = entity.getCurrentFrame().x;
    src.y = entity.getCurrentFrame().y;
    src.w = entity.getCurrentFrame().w;
    src.h = entity.getCurrentFrame().h;

    SDL_Rect dest;
    dest.x = entity.getPosition().x;
    dest.y = entity.getPosition().y;
    dest.w = entity.getWidth();
    dest.h = entity.getHeight();

    SDL_RenderCopy(renderer, entity.getTexture(), &src, &dest);
}

void RenderWindow::render(Square& square)
{
    SDL_Rect src;
    src.x = square.getCurrentFrame().x;
    src.y = square.getCurrentFrame().y;
    src.w = square.getCurrentFrame().w;
    src.h = square.getCurrentFrame().h;

    SDL_Rect dest;
    dest.x = square.getPosition().x;
    dest.y = square.getPosition().y;
    dest.w = square.getWidth();
    dest.h = square.getHeight();

    std::array<int, 4> color = square.getColor();

    SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
    SDL_RenderFillRect(renderer, &dest);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderDrawRect(renderer, &dest);
    SDL_RenderCopy(renderer, square.getTexture(), &src, &dest);
    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
}

void RenderWindow::render(Board& board)
{
    for(Square& s : board.getSquares())
    {
        render(s);
    }
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            renderBox(Vector2f(board.getStartPoint().x + j * 3 * board.getSquareSize(), board.getStartPoint().y + i * 3 * board.getSquareSize()), 3 * board.getSquareSize(), 3 * board.getSquareSize());
        }
    }
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::showMessageBox(const char* message)
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Sudoku", message, window);
}
