#include "vector2f.h"
#include <cmath>

const Vector2f Vector2f::Zero(0.0f, 0.0f);

Vector2f::Vector2f()
{
    x = 0.f;
    y = 0.f;
}

Vector2f::Vector2f(float x, float y): x(x), y(y)
{

}

float Vector2f::Distance(Vector2f a, Vector2f b)
{
    Vector2f vec = a-b;
    return vec.Magnitude();
}

void Vector2f::Reassign(float newX, float newY)
{
    this->x = newX;
    this->y = newY;
}

float Vector2f::Magnitude()const
{
    return std::sqrt(std::pow(this->x,2) + std::pow(this->y,2));
}

void Vector2f::Normalize()
{
    *this /= this->Magnitude();
}

Vector2f Vector2f::Normalized()const
{
    return *this/this->Magnitude();
}

//Relational Operators/////////////////////////////////////////////////////////
bool Vector2f::operator ==(const Vector2f &rhs)const
{
    return(this->x == rhs.x && this->y == rhs.y);
}

bool Vector2f::operator !=(const Vector2f &rhs)const
{
    return !(*this == rhs);
}
//Assignment Operators With Vectors////////////////////////////////////
Vector2f &Vector2f::operator =(const Vector2f &rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
}

Vector2f &Vector2f::operator +=(const Vector2f &rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

Vector2f &Vector2f::operator -=(const Vector2f &rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

Vector2f &Vector2f::operator *=(const Vector2f &rhs)
{
    this->x *= rhs.x;
    this->y *= rhs.y;
    return *this;
}
//Arithmetic Operators With Vectors/////////////////////////////////////////////
Vector2f Vector2f::operator +(const Vector2f &rhs)const
{
    return Vector2f(this->x + rhs.x, this->y + rhs.y);
}

Vector2f Vector2f::operator -(const Vector2f &rhs)const
{
    return Vector2f(this->x - rhs.x, this->y - rhs.y);
}

Vector2f Vector2f::operator -()const
{
    return Vector2f(-this->x, -this->y);
}

Vector2f Vector2f::operator *(const Vector2f &rhs)const
{
    return Vector2f(this->x * rhs.x, this->y * rhs.y);
}
//Assignment Operators With Scalars///////////////////////////////////////////////
Vector2f &Vector2f::operator *=(const float &rhs)
{
    this->x *= rhs;
    this->y *= rhs;
    return *this;
}

Vector2f &Vector2f::operator /=(const float &rhs)
{
    this->x /= rhs;
    this->y /= rhs;
    return *this;
}
//Arithmetic Operators With Scalars/////////////////////////////////////////////
Vector2f Vector2f::operator *(const float &rhs)const
{
    return Vector2f(this->x * rhs, this->y * rhs);
}

Vector2f Vector2f::operator /(const float &rhs)const
{
    return Vector2f(this->x / rhs, this->y / rhs);
}
