#ifndef COLOR_H
#define COLOR_H

#include "platform.h"

struct Color
{
	float r, g, b, a;
	Color(float r_, float g_, float b_, float a_) :
		r(r_), g(g_), b(b_), a(a_)	
	{}
};

static Color COLOR_WITHE(1, 1, 1, 1);
static Color COLOR_RED(1,0,0,1);
static Color COLOR_BLUE(0, 0, 1, 1);
static Color COLOR_GREEN(0, 1, 0, 1);


#endif
