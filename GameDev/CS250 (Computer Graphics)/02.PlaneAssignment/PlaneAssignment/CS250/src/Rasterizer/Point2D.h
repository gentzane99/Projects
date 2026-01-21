#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>

const int DIMENSION = 3;

class Point2D
{
  public:
    Point2D(float x = 0.0f, float y = 0.0f, float _z = 0.0f, float red = 0, float green = 0, float blue = 0);
    Point2D(const Point2D & rhs);

    Point2D & operator=(const Point2D & rhs);
    Point2D   operator-(void) const;

    union
    {
        float val[DIMENSION]; /* 2D coordinates */
        struct
        {
            float x, y, z;
        };
    };
    union
    {
        float col[3]; /* Color values RGB */
        struct
        {
            float r, g, b;
        };
    };
};

#endif