/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    Point4.cpp
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS250
 \par     Programming Assignment #1
 \date    1/8/2020
 \brief   Function definitions for Point4 class.
******************************************************************************/
#include "Point4.h" //Point4

/*!****************************************************************************
 \brief Default constructor, sets x,y,z to zero and w to the defined value
******************************************************************************/
Point4::Point4(void): x(0.0f), y(0.0f), z(0.0f), w(1.0f){}

/*!****************************************************************************
 \brief Copy constructor, copies every component from the other Point4
 \param const Point4 & - Point to copy
******************************************************************************/
Point4::Point4(const Point4& rhs): x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w){}

/*!****************************************************************************
 \brief Non default contructor
 \param Values of the given point
******************************************************************************/
Point4::Point4(float xx, float yy, float zz, float ww): x(xx), y(yy), z(zz), w(ww) {}

/*!****************************************************************************
 \brief Assignment operator, copies every component from the other Point4
 \param const Point4 & - Point to copy
 \result Point4 & - Copied point
******************************************************************************/
Point4& Point4::operator=(const Point4& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;

    return *this;
}

/*!****************************************************************************
 \brief Unary negation operator, negates every component
 \return Point4 - Obtained negated point
******************************************************************************/
Point4 Point4::operator-(void) const
{
    return Point4(-x, -y, -z, -w);
}

/*!****************************************************************************
 \brief Binary subtraction operator, subtract two Point4s
 \param const Point4 & - Point to substract with
 \return Vector4 - Obtained vector from the substraction of the points
******************************************************************************/
Vector4 Point4::operator-(const Point4& rhs) const  
{
    return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

/*!****************************************************************************
 \brief Adds a given vector to the point
 \param const Vector4 & - Vector to add
 \return Point4 - Obtained point
******************************************************************************/
Point4 Point4::operator+ (const Vector4& rhs) const
{
    return Point4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

/*!****************************************************************************
 \brief Substracts a given vector to the point
 \param const Vector4 & - Vector to substract
 \return Point4 - Obtained point
******************************************************************************/
Point4 Point4::operator- (const Vector4& rhs) const
{
    return Point4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

/*!****************************************************************************
 \brief Adds a given vector to the point
 \param const Vector4 & - Vector to add
 \return Point4 & - Reference to the obtained point
******************************************************************************/
Point4& Point4::operator+=(const Vector4& rhs)
{
    return *this = *this + rhs;
}

/*!****************************************************************************
 \brief Substracts a given vector to the point
 \param const Vector4 & - Vector to substract
 \return Point4 & - Reference to the obtained point
******************************************************************************/
Point4& Point4::operator-=(const Vector4& rhs)
{
    return *this = *this - rhs;
}

/*!****************************************************************************
 \brief Comparision operator ==
 \param const Point4 & - Point to compare with
 \return bool - Returns if the points are equal or not
******************************************************************************/
bool Point4::operator==(const Point4& rhs) const
{
    return isEqual(x, rhs.x) && isEqual(y, rhs.y) && isEqual(z, rhs.z) && isEqual(w, rhs.w);
}

/*!****************************************************************************
 \brief Comparision operator !=
 \param const Point4 & - Point to compare with
 \return bool - Returns if the points are equal or not
******************************************************************************/
bool Point4::operator!=(const Point4& rhs) const
{
    return !(isEqual(x, rhs.x) && isEqual(y, rhs.y) && isEqual(z, rhs.z) && isEqual(w, rhs.w));
}

/*!****************************************************************************
 \brief Sets x,y,z to zeroes, w to defined value
******************************************************************************/
void Point4::Zero(void)
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 1.0f;
}