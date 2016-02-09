#ifndef VECTOR2F_H
#define VECTOR2F_H

//Over engineered for this project, however it was pulled from another one.

class Vector2f
{
public:
    Vector2f();
    Vector2f(float x, float y);

    float x,y;
    static const Vector2f Zero;
    //Utillity Functions
    static float Distance(Vector2f a, Vector2f b);
    void Reassign(float newX, float newY);
    float Magnitude()const;
    void Normalize();
    Vector2f Normalized()const;
    //Relational Operators
    bool operator ==(const Vector2f &rhs)const;
    bool operator !=(const Vector2f &rhs)const;
    //Assignment Operators With Vectors
    Vector2f &operator =(const Vector2f &rhs);
    Vector2f &operator +=(const Vector2f &rhs);
    Vector2f &operator -=(const Vector2f &rhs);
    Vector2f &operator *=(const Vector2f &rhs);

    //Arithmetic Operators With Vectors
    Vector2f operator +(const Vector2f &rhs)const;
    Vector2f operator -(const Vector2f &rhs)const;
    Vector2f operator -()const;
    Vector2f operator *(const Vector2f &rhs)const;

    //Assignment Operators With Scalars
    Vector2f &operator *=(const float &rhs);
    Vector2f &operator /=(const float &rhs);

    //Arithmetic Operators With Scalars
    Vector2f operator *(const float &rhs)const;
    Vector2f operator /(const float &rhs)const;
};

#endif
