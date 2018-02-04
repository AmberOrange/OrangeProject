#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP
#include "Graphics.hpp"
class Drawable
{
public:
	virtual void draw(Graphics &rGraphics) = 0;
};

#endif