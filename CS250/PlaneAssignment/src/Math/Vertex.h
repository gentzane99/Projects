#pragma once

#include <SFML/Graphics.hpp>
#include "Math/Point4.h"

namespace Rasterizer
{
	// PROVIDED
	/// -----------------------------------------------------------------------
	/// \class	Vertex
	///	\brief	Simple structure used to define a triangle vertex with both position
	///			and color attribute. 
	struct Vertex
	{
		Point4  mPosition;	// x,y,z,w
		sf::Color	mColor;		// r,g,b,a
	};
	
}