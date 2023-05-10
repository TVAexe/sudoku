#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <ctime>

#include "RenderWindow.hpp"
#include "Mouse.hpp"
#include "Entity.hpp"
#include "Board.hpp"
#include "Square.hpp"
#include "Vector2f.hpp"

#define WINDOW_WIDTH window.getWidth()
#define WINDOW_HEIGHT window.getHeight()
#define SQUARE_SIZE SDL_min(WINDOW_WIDTH / 12, WINDOW_HEIGHT / 18)
#define BOARD_START_X (WINDOW_WIDTH - 9 * SQUARE_SIZE) * 0.5
#define BOARD_START_Y 120

void menu();
void game();
void help();

bool isRunning = true;

// Window, background, and textures
RenderWindow window("Sudoku", 480, 720);

SDL_Cursor *SDL_CURSOR_ARROW = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
SDL_Cursor *SDL_CURSOR_HAND = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

void init()
{
    // SDL Init and cursor init
    if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
        std::cout << "[ERROR] Failed Init: " << SDL_GetError() << std::endl;
    if (!IMG_Init(IMG_INIT_PNG))
        std::cout << "[ERROR] Failed Image Init: " << SDL_GetError() << std::endl;
}

void game()
{

    SDL_Texture *backgroundTexture = window.loadTexture("res/images/bg.png");
    SDL_Texture *restartButtonTexture = window.loadTexture("res/images/restart.png");
    Entity background(Vector2f(0, 0), window.getWidth(), window.getHeight(), backgroundTexture);
    Entity restartButton(Vector2f(25, 25), 30, 30, restartButtonTexture);

    std::vector<SDL_Texture *> numberTextures;
    window.loadTextures("res/dev/texture_list.txt", numberTextures);

    // Board
    Board board(Vector2f(BOARD_START_X, BOARD_START_Y), numberTextures);

    Mouse mouse;
    SDL_Event event;

    // Program loop
    while (isRunning)
    {
        int startTick = SDL_GetTicks();

        // Event handler
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    window.updateSize();
                    background.setWidth(WINDOW_WIDTH);
                    background.setHeight(WINDOW_HEIGHT);
                    board.resize(Vector2f(BOARD_START_X, BOARD_START_Y), SQUARE_SIZE);
                }
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (mouse.isInsideEntity(restartButton))
                    {
                        board.restart();
                    }
                    board.updateSelected(mouse);
                }
                break;

            case SDL_KEYDOWN:
                board.setSelectedSquareValue(event.key.keysym.sym);
                break;

            default:
                break;
            }
        }

        if (mouse.isInsideEntity(restartButton))
            SDL_SetCursor(SDL_CURSOR_HAND);
        else
            SDL_SetCursor(SDL_CURSOR_ARROW);

        window.clearScreen();

        window.render(background);
        window.render(restartButton);

        board.setAllSquareColor(255, 255, 255, 255);
        board.update(mouse);

        window.render(board);
        window.display();

        // Timestep management
        int frameTicks = SDL_GetTicks() - startTick;
        if (frameTicks < 1000 / window.getRefreshRate())
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
    }
}

void menu()
{
    SDL_Texture *menuTexture = window.loadTexture("res/images/menu.png");
    Entity menuBackground(Vector2f(0, 0), window.getWidth(), window.getHeight(), menuTexture);
    Entity playButton(Vector2f(144, 373), 192, 54, NULL);
    Entity helpButton(Vector2f(144, 486), 192, 54, NULL);
    Entity quitButton(Vector2f(144, 600), 192, 54, NULL);

    Mouse mouse;
    SDL_Event event;

    // Program loop
    while (isRunning)
    {
        int startTick = SDL_GetTicks();

        // Event handler
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (mouse.isInsideEntity(playButton))
                    {
                        game();
                    }

                    if (mouse.isInsideEntity(helpButton))
                    {
                        help();
                    }

                    if (mouse.isInsideEntity(quitButton))
                    {
                        isRunning = false;
                    }
                }
                break;

            default:
                break;
            }
        }

     
        window.render(menuBackground);
        window.render(playButton);
        window.render(helpButton);
        window.render(quitButton);

        window.display();

        // Timestep management
        int frameTicks = SDL_GetTicks() - startTick;
        if (frameTicks < 1000 / window.getRefreshRate())
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
    }
}

void help()
{
    SDL_Texture *helpTexture = window.loadTexture("res/images/help.png");
    Entity helpBackground(Vector2f(0, 0), window.getWidth(), window.getHeight(), helpTexture);
    Entity backButton(Vector2f(48, 30), 195, 35, NULL);

    Mouse mouse;
    SDL_Event event;

    // Program loop
    while (isRunning)
    {
        int startTick = SDL_GetTicks();

        // Event handler
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (mouse.isInsideEntity(backButton))
                    {
                        menu();
                    }
                }
                break;

            default:
                break;
            }
        }

        window.render(helpBackground);
        window.render(backButton);

        window.display();

        // Timestep management
        int frameTicks = SDL_GetTicks() - startTick;
        if (frameTicks < 1000 / window.getRefreshRate())
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
    }
}

int main(int argc, char *argv[])
{
    // Random seed
    srand(time(NULL));

    init();

    menu();

    window.clean();
    SDL_Quit();

    return 0;
}
