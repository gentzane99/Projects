/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    Vector4.cpp
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS250
 \par     Programming Assignment #1
 \date    1/8/2020
 \brief   Function definitions for Vector4 class.
******************************************************************************/
#include "Vector4.h" //Vector4
#include <math.h> //sqrt

/*!****************************************************************************
 \brief Default constructor, initializes x,y,z to zeroes, w to defined value
******************************************************************************/
Vector4::Vector4(void): x(0.0f), y(0.0f), z(0.0f), w(0.0f){}

/*!****************************************************************************
 \brief Copy constructor, copies every component from the other Vector4
 \param const Vector4 & - Vector to copy
******************************************************************************/
Vector4::Vector4(const Vector4& rhs): x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w){}

/*!****************************************************************************
 \brief Non default contructor
 \param Values of the given vector
******************************************************************************/
Vector4::Vector4(float xx, float yy, float zz, float ww): x(xx), y(yy), z(zz), w(ww) {}

/*!****************************************************************************
 \brief Assignment operator, copies every component from the other Vector4
 \param const Vector4 & - Vector to copy
 \result Vector4 & - Copied vector
******************************************************************************/
Vector4& Vector4::operator=(const Vector4& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
}

/*!****************************************************************************
 \brief Unary negation operator, negates every component
 \return Vector4 - Obtained negated vector
******************************************************************************/
Vector4 Vector4::operator-(void) const
{ 
    return Vector4(-x, -y, -z, -w);
}

/*!****************************************************************************
 \brief Adds a given vector to the vector
 \param const Vector4 & - Vector to add
 \return Vector4 - Obtained vector
******************************************************************************/
Vector4 Vector4::operator+(const Vector4& rhs) const
{
    return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

/*!****************************************************************************
 \brief Substracts a given vector to the vector
 \param const Vector4 & - Vector to substract
 \return Vector4 - Obtained vector
******************************************************************************/
Vector4 Vector4::operator-(const Vector4& rhs) const
{
    return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

/*!****************************************************************************
 \brief Multiplies a given number to the vector
 \param const float - Number to multiply
 \return Vector4 - Obtained vector
******************************************************************************/
Vector4 Vector4::operator*(const float rhs) const
{
    return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
}

/*!****************************************************************************
 \brief Divides a given number to the vector
 \param const float - Number to divide
 \return Vector4 - Obtained vector
******************************************************************************/
Vector4 Vector4::operator/(const float rhs) const
{
    return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
}

/*!****************************************************************************
 \brief Adds a given vector to the vector
 \param const Vector4 & - Vector to add
 \return Vector4& - Reference to the obtained vector
******************************************************************************/
Vector4& Vector4::operator+=(const Vector4& rhs)
{
    return *this = *this + rhs;
}

/*!****************************************************************************
 \brief Substracts a given vector to the vector
 \param const Vector4 & - Vector to substract
 \return Vector4& - Reference to the obtained vector
******************************************************************************/
Vector4& Vector4::operator-=(const Vector4& rhs)
{
    return *this = *this - rhs;
}

/*!****************************************************************************
 \brief Multiplies a given number to the vector
 \param const float - Number to multiply
 \return Vector4 - Reference to the obtained vector
******************************************************************************/
Vector4& Vector4::operator*=(const float rhs)
{
    return *this = *this * rhs;
}

/*!****************************************************************************
 \brief Divides a given number to the vector
 \param const float - Number to divide
 \return Vector4 - Reference to the obtained vector
******************************************************************************/
Vector4& Vector4::operator/=(const float rhs)
{
    return *this = *this / rhs;
}

/*!****************************************************************************
 \brief Comparision operator ==
 \param const Vector4 & - Vector to compare with
 \return bool - Returns if the vectors are equal or not
******************************************************************************/
bool Vector4::operator==(const Vector4& rhs) const
{
    return isEqual(x, rhs.x) && isEqual(y, rhs.y) && isEqual(z, rhs.z) && isEqual(w, rhs.w);
}

/*!****************************************************************************
 \brief Comparision operator !=
 \param const Vector4 & - Vector to compare with
 \return bool - Returns if the vectors are equal or not
******************************************************************************/
bool Vector4::operator!=(const Vector4& rhs) const
{
   return !(isEqual(x, rhs.x) && isEqual(y, rhs.y) && isEqual(z, rhs.z) && isEqual(w, rhs.w));
}

/*!****************************************************************************
 \brief Computes the dot product
 \param const Vector4 & - Vector to compute the dot product with
 \result Vector4 - Result of the dot product
******************************************************************************/
float Vector4::Dot(const Vector4& rhs) const
{
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

/*!****************************************************************************
 \brief Computes the cross product
 \param const Vector4 & - Vector to compute the cross product with
 \result Vector4 - Resulting vector of the cross product
******************************************************************************/
Vector4 Vector4::Cross(const Vector4& rhs) const
{
    return Vector4(y * rhs.z - z * rhs.y, -(x * rhs.z - z * rhs.x), x * rhs.y - y * rhs.x);
}

/*!****************************************************************************
 \brief Computes the true length of the vector
\return float - Value of the length
******************************************************************************/
float Vector4::Length(void) const
{
    return sqrtf(x*x + y*y + z*z + w*w);
}

/*!****************************************************************************
 \brief Computes the squared length of the vector
 \return float - Value of the squared length
******************************************************************************/
float Vector4::LengthSq(void) const
{
    return x*x + y*y + z*z + w*w;
}

/*!****************************************************************************
 \brief Normalizes the vector to make the final vector be of length 1
******************************************************************************/
void Vector4::Normalize(void)
{
   float length = Length();
    if(!isZero(length))
    {
        x /= length;
        y /= length;
        z /= length;
        w /= length;
    }
}

/*!****************************************************************************
 \brief Sets x,y,z to zeroes, w to defined value
******************************************************************************/
void Vector4::Zero(void)
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    w = 0.0f;
}