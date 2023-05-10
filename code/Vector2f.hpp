#pragma once

class Vector2f
{
    public:
        Vector2f();
        Vector2f(float pX, float pY);
        void operator=(Vector2f vector);
        Vector2f operator+(Vector2f other);
        Vector2f operator-(Vector2f other);
        Vector2f operator*(float scalar);
        float dotProduct(Vector2f other);
        float getSquaredMagnitude();
       void print();
        
        float x, y;
};
