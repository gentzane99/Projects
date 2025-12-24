/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    Matrix4.cpp
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS250
 \par     Programming Assignment #1
 \date    1/8/2020
 \brief   Function definitions for Matrix4 class.
******************************************************************************/
#include "Matrix4.h" //Matrix4

/*!****************************************************************************
 \brief   Default constructor should initialize to zeroes
******************************************************************************/
Matrix4::Matrix4(void)
{
	Zero();
}

/*!****************************************************************************
 \brief  Copy constructor, copies every entry from the other matrix
 \param const Matrix4 & - Matrix to copy
******************************************************************************/
Matrix4::Matrix4(const Matrix4& rhs)
{
	for(unsigned i = 0; i < 16; i++)
		v[i] = rhs.v[i];
}

/*!****************************************************************************
 \brief  Non-default constructor
 \param Values of the given matrix
******************************************************************************/
Matrix4::Matrix4(float mm00, float mm01, float mm02, float mm03,
float mm10, float mm11, float mm12, float mm13,
float mm20, float mm21, float mm22, float mm23,
float mm30, float mm31, float mm32, float mm33)
{
	v[0]=mm00;
	v[1]=mm01;
	v[2]=mm02;
	v[3]=mm03;
	v[4]=mm10;
	v[5]=mm11;
	v[6]=mm12;
	v[7]=mm13;
	v[8]=mm20;
	v[9]=mm21;
	v[10]=mm22;
	v[11]=mm23;
	v[12]=mm30;
	v[13]=mm31;
	v[14]=mm32;
	v[15]=mm33;
}

/*!****************************************************************************
 \brief Assignment operator, copies every component from the other Matrix4
 \param const Matrix4 & - Matrix to copy
 \result Matrix4 & - Copied matrix
******************************************************************************/
Matrix4& Matrix4::operator=(const Matrix4& rhs)
{
	for(unsigned i = 0; i < 16; i++)
		v[i] = rhs.v[i];

    return *this;
}

/*!****************************************************************************
 \brief  Multiplying a Matrix4 with a Vector4 
 \param const Vector4 & - Vector to multiply with
 \return Vector4 - Obtained vector
******************************************************************************/
Vector4 Matrix4::operator*(const Vector4& rhs) const
{
	Vector4 vec; 

	for(unsigned i = 0; i < 4; i++)
	{
		for(unsigned j = 0; j < 4; j++)
		{
			vec.v[i] += m[i][j] * rhs.v[j];
		}
	}
	return vec;
}

/*!****************************************************************************
 \brief  Multiplying a Matrix4 with a Point4 
 \param const Point4 & - Point to multiply with
 \return Point4 - Obtained point
******************************************************************************/
Point4 Matrix4::operator*(const Point4& rhs) const
{
	Point4 point(0.0f, 0.0f, 0.0f, 0.0f);

	for(unsigned i = 0; i < 4; i++)
	{
		for(unsigned j = 0; j < 4; j++)
		{
			point.v[i] += m[i][j] * rhs.v[j];
		}
	}
	return point;
}

/*!****************************************************************************
 \brief Adds a given matrix to the matrix
 \param const Matrix4 & - Matrix4 to add
 \return Matrix4 - Obtained matrix
******************************************************************************/
Matrix4 Matrix4::operator+(const Matrix4& rhs) const
{
	Matrix4 mat;

	for(unsigned i = 0; i < 16; i++)
		mat.v[i] = v[i] + rhs.v[i];

	return mat;
}

/*!****************************************************************************
 \brief Substracts a given matrix to the matrix
 \param const Matrix4 & - Matrix4 to substract
 \return Matrix4 - Obtained matrix
******************************************************************************/
Matrix4 Matrix4::operator-(const Matrix4& rhs) const
{
	Matrix4 mat;

	for(unsigned i = 0; i < 16; i++)
		mat.v[i] = v[i] - rhs.v[i];

	return mat;
}

/*!****************************************************************************
 \brief Multiplies a given matrix to the matrix
 \param const Matrix4 & - Matrix4 to multiply
 \return Matrix4 - Obtained matrix
******************************************************************************/
Matrix4 Matrix4::operator*(const Matrix4& rhs) const
{
	Matrix4 mat;

	float result;
	
	for(unsigned i = 0; i < 4; i++)
	{
		for(unsigned j = 0; j < 4; j++)
		{
			result = 0;
			for(unsigned k = 0; k < 4; k++)
			{
				result += m[i][k] * rhs.m[k][j];
			}
			mat.m[i][j] = result;
		}
	}
	return mat;
}

/*!****************************************************************************
 \brief Adds a given matrix to the matrix
 \param const Matrix4 & - Matrix4 to add
 \return Matrix4 & - Reference to the obtained matrix
******************************************************************************/
Matrix4& Matrix4::operator+=(const Matrix4& rhs)
{
    return *this = *this + rhs;
}

/*!****************************************************************************
 \brief Substracts a given matrix to the matrix
 \param const Matrix4 & - Matrix4 to substract
 \return Matrix4 & - Reference to the obtained matrix
******************************************************************************/
Matrix4& Matrix4::operator-=(const Matrix4& rhs)
{
    return *this = *this - rhs;
}

/*!****************************************************************************
 \brief Multiply a given matrix to the matrix
 \param const Matrix4 & - Matrix4 to multiply
 \return Matrix4 & - Reference to the obtained matrix
******************************************************************************/
Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
	return *this = *this * rhs;
}

/*!****************************************************************************
 \brief Multiplies a given number to the matrix
 \param const float - Number to multiply
 \return Matrix4 - Obtained matrix
******************************************************************************/
Matrix4 Matrix4::operator*(const float rhs) const
{
	Matrix4 mat;
	for(unsigned i = 0; i < 16; i++)
	{
		mat.v[i] = v[i] * rhs;
	}
    return mat;
}

/*!****************************************************************************
 \brief Divides a given number to the matrix
 \param const float - Number to multiply
 \return Matrix4 - Obtained matrix
******************************************************************************/
Matrix4 Matrix4::operator/(const float rhs) const
{
	Matrix4 mat;
	for(unsigned i = 0; i < 16; i++)
		mat.v[i] = v[i] / rhs;
    return mat;
}

/*!****************************************************************************
 \brief Multiplies a given number to the matrix
 \param const float - Number to multiply
 \return Matrix4 & - Reference to the obtained matrix
******************************************************************************/
Matrix4& Matrix4::operator*=(const float rhs)
{
    return *this = *this * rhs;
}

/*!****************************************************************************
 \brief Divides a given number to the matrix
 \param const float - Number to multiply
 \return Matrix4 & - Reference to the obtained matrix
******************************************************************************/
Matrix4& Matrix4::operator/=(const float rhs)
{	
    return *this = *this / rhs;
}

/*!****************************************************************************
 \brief Comparision operator ==
 \param const Matrix4 & - Matrix to compare with
 \return bool - Returns if the matrices are equal or not
******************************************************************************/
bool Matrix4::operator==(const Matrix4& rhs) const
{
	for(unsigned i = 0; i < 16; i++)
	{
		if(!(isEqual(v[i], rhs.v[i])))
			return false;
	}

	return true;
}

/*!****************************************************************************
 \brief Comparision operator !=
 \param const Matrix4 & - Matrix to compare with
 \return bool - Returns if the matrices are equal or not
******************************************************************************/
bool Matrix4::operator!=(const Matrix4& rhs) const
{
	return !(*this == rhs);
}

/*!****************************************************************************
 \brief Zeroes out the entire matrix
******************************************************************************/
void Matrix4::Zero(void)
{
	for(unsigned i = 0; i < 16; i++)
	{
		v[i] = 0.0f;
	}
}

/*!****************************************************************************
 \brief  Builds the identity matrix
******************************************************************************/
void Matrix4::Identity(void)
{
	for(unsigned i = 0; i < 4; i++)
	{
		for(unsigned j = 0; j < 4; j++)
		{
			if(i == j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
		}	
	}
}