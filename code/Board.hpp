#pragma once

#include<vector>

#include "Vector2f.hpp"
#include "Mouse.hpp"
#include "Square.hpp"

class Board
{
public:
    Board(Vector2f pStartPoint, std::vector<SDL_Texture*>& pSquareTextures);
    void resize(Vector2f pStartPoint, float newSize);
    void restart();
    void updateSelected(Mouse& mouse);
    void update(Mouse& mouse);
    Vector2f& getStartPoint();
    std::vector<Square>& getSquares();
    float getSquareSize();
    void setAllSquareColor(int r, int g, int b, int a);
    void setSelectedSquareValue(char key);
private:
    std::vector<SDL_Texture*> squareTextures;
    std::vector<Square> squares;
    Vector2f startPoint;
    float squareSize;
    std::vector<std::string> generateProblem();
};