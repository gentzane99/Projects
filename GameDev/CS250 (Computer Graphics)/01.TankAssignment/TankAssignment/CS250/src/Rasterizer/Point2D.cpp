#include "Point2D.h"
#include <iostream> // cout

Point2D::Point2D(float _x, float _y, float red, float green, float blue)
{
    val[0] = _x;
    val[1] = _y;
    val[2] = 1.0f;

    col[0] = red;
    col[1] = green;
    col[2] = blue;
}

Point2D::Point2D(const Point2D & rhs)
{
    val[0] = rhs.val[0];
    val[1] = rhs.val[1];
    val[2] = rhs.val[2];

    col[0] = rhs.col[0];
    col[1] = rhs.col[1];
    col[2] = rhs.col[2];
}

Point2D & Point2D::operator=(const Point2D & rhs)
{
    if (this != &rhs)
    {
        val[0] = rhs.val[0];
        val[1] = rhs.val[1];
        val[2] = rhs.val[2];

        col[0] = rhs.col[0];
        col[1] = rhs.col[1];
        col[2] = rhs.col[2];
    }

    return *this;
}

Point2D Point2D::operator-(void) const
{
    return Point2D(-val[0], -val[1]);
}
