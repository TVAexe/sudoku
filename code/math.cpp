#include<iostream>

#include "Vector2f.hpp"

//Vector
Vector2f::Vector2f()
{
    x = 0.0f; y = 0.0f;
}

Vector2f::Vector2f(float pX, float pY)
{
    x = pX; y = pY;
}

void Vector2f::operator=(Vector2f vector)
{
    x = vector.x;
    y = vector.y;
}

Vector2f Vector2f::operator+(Vector2f other)
{
    return Vector2f((x + other.x), (y + other.y));
}

Vector2f Vector2f::operator-(Vector2f other)
{
    return Vector2f((x - other.x), (y - other.y));
}

Vector2f Vector2f::operator*(float scalar)
{
    return Vector2f((x * scalar), (y * scalar));
}

float Vector2f::dotProduct(Vector2f other)
{
    return (x * other.x) + (y * other.y);
}

float Vector2f::getSquaredMagnitude()
{
    return (x * x + y * y);
}

void Vector2f::print()
{
    std::cout << "{" << x << ", " << y << "}" << std::endl;
}




