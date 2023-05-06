#pragma once

#include<array>
#include<vector>

#include "code/Vector2f.hpp"
#include "code/Entity.hpp"

class Square : public Entity
{
public:
    Square();
    Square(Vector2f pPos, int pRow, int pColumn, int pValue, int pCorrectValue, SDL_Texture* pTexture);
    void generateRelatives(std::vector<Square>& squares);
    void updateAnswer(int pValue, int pCorrectValue);
    bool isAnswerFalse();
    bool isRedTexture();
    void select();
    void deselect();
    int getValue();
    int getRow();
    int getColumn();
    int getGroupRow();
    int getGroupColumn();
    std::array<int, 4>& getColor();
    std::vector<Square*> getRelatives();
    bool isSelected();
    void setTexture(SDL_Texture* pTexture);
    void setSize(float pSize);
    void setColor(int r, int g, int b, int a);
    void writePen(int pValue);
    void writePencil(int pValue);
private:
    int value, correctValue;
    int row, column, groupRow, groupColumn;
    bool selected;
    std::array<int, 4> color;
    std::array<bool, 9> pencil;
    std::vector<Square*> relatives;
};
