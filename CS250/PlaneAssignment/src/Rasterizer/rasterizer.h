/*!****************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.

 \file    rasterizer.h
 \author  Gentzane Pastor // gentzane.pastor@digipen.edu // 540000217
 \par     Course: CS250
 \par     Programming Assignment #2
 \date    02/11/2020
 \brief   Function declarations for DrawMidpointLine and DrawTriangleSolid
******************************************************************************/
#pragma once

#include "Rasterizer/Point2D.h" //Point2d
#include <SFML/Graphics.hpp> // sf::Image, sf::Color

/*!****************************************************************************
 \brief Draws a line throught 2 points
 \param const Point2D & - First point of the line
 \param const Point2D & - Second point of the line
 \param sf::Image & - Reference to the image created in main
******************************************************************************/
void DrawMidpointLine(const Point2D &, const Point2D &, sf::Image &);

/*!****************************************************************************
 \brief Draws a triangle
 \param const Point2D & - First point of the triangle
 \param const Point2D & - Second point of the triangle
 \param const Point2D & - Third point of the triangle
 \param sf::Image & - Reference to the image created in main
******************************************************************************/
void DrawTriangleSolid(const Point2D & p0, const Point2D & p1, const Point2D & p2, sf::Image & image, std::vector<float> & ZBuffer_);