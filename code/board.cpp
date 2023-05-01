#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>

#include "code/Vector2f.hpp"
#include "code/Mouse.hpp"
#include "code/Square.hpp"
#include "code/Board.hpp"

#define CORRECT_TEXTURE(x) squareTextures[x.getValue()]
#define WRONG_TEXTURE(x) squareTextures[x.getValue() + 9]

Board::Board(Vector2f pStartPoint, std::vector<SDL_Texture*>& pSquareTextures)
{
    const std::vector<std::string> chosenProblem = generateProblem();
    
    startPoint = pStartPoint;
    squareSize = 40;
    squares.resize(81);
    squareTextures.assign(pSquareTextures.begin(), pSquareTextures.end());
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            squares[9 * i + j] = Square(Vector2f(startPoint + Vector2f(j * squareSize, i * squareSize)), i, j, chosenProblem[0].at(9 * i + j) - '0', chosenProblem[1].at(9 * i + j) - '0', squareTextures[chosenProblem[0].at(9 * i + j) - '0']);
        }
    }
    for(Square& s : squares)
    {
        s.generateRelatives(squares);
    }
}

std::vector<std::string> Board::generateProblem()
{
    const int random = (rand() % 1000) + 1;
    std::string chosenLine;
    std::vector<std::string> chosenProblem;
    std::ifstream problemData("res/dev/sudoku.csv");
    for(int i = 1; std::getline(problemData, chosenLine); i++)
    {
        if(i == random) break;
    }
    chosenProblem.push_back(chosenLine.substr(0, 81));
    chosenProblem.push_back(chosenLine.substr(82));
    return chosenProblem;
}

void Board::resize(Vector2f pStartPoint, float newSize)
{
    startPoint = pStartPoint;
    squareSize = newSize;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            squares[9 * i + j].setSize(newSize);
            squares[9 * i + j].setPosition(startPoint.x + j * newSize, startPoint.y + i * newSize);
        }
    }
}

void Board::restart()
{
    const std::vector<std::string> chosenProblem = generateProblem();
    for(int i = 0; i < 81; i++)
    {
        std::cout << chosenProblem[1].at(i);
        if(i % 3 == 2) std::cout << " ";
        if(i % 9 == 8) std::cout << std::endl;
        if(i % 27 == 26) std::cout << std::endl;
    }
    std::cout << "=================================" << std::endl;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            squares[9 * i + j].updateAnswer(chosenProblem[0].at(9 * i + j) - '0', chosenProblem[1].at(9 * i + j) - '0');
            squares[9 * i + j].setTexture(squareTextures[chosenProblem[0].at(9 * i + j) - '0']);
        }
    }
}

void Board::updateSelected(Mouse& mouse)
{
    bool noSquareSelected = true;
    for(Square& s : squares)
    {
        if(mouse.isInsideEntity(s))
        {
            for(Square& other : squares)
            {
                other.deselect();
            }
            s.select();
            noSquareSelected = false;
        }
    }
    if(noSquareSelected)
    {
        for(Square& s : squares)
        {
            s.deselect();
        }
    }
}

void Board::update(Mouse& mouse)
{
    for(Square& s : squares)
    {
        // when mouse is inside a square (cell)
        if(mouse.isInsideEntity(s))
        {
            for(Square* r : s.getRelatives())
            {
                if(r->getColor()[0] != 147 && r->getColor()[0] != 112)
                    r->setColor(200, 200, 200, 255); // Light gray
            }
            if(s.getColor()[0] != 147 && s.getColor()[0] != 112) // s not light blue and not dark blue
                s.setColor(165, 165, 165, 255); // Dark gray
        }

        // when a cell is selected
        if(s.isSelected())
        {
            for(Square* r : s.getRelatives())
            {
                r->setColor(147, 198, 249, 255); // Light blue
            }
            s.setColor(112, 163, 214, 255); // Dark blue
        }

        //when a cell has wrong answer
        s.setTexture(!s.isRedTexture() ? CORRECT_TEXTURE(s) : WRONG_TEXTURE(s));
    }
}

Vector2f& Board::getStartPoint()
{
    return startPoint;
}

std::vector<Square>& Board::getSquares()
{
    return squares;
}

float Board::getSquareSize()
{
    return squareSize;
}

void Board::setAllSquareColor(int r, int g, int b, int a)
{
    for(Square& s : squares)
    {
        s.setColor(r, g, b, a);
    }
}

void Board::setSelectedSquareValue(char key)
{
    if(key == '\b' || (key >= '1' && key <= '9'))
    {
        for(Square& s : squares)
        {
            if(s.isSelected()) s.writePen((key == '\b') ? 0 : key - '0');
        }
    }
}
