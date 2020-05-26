#pragma once
#include <Siv3D.hpp>

class ParrotContainer
{
	Color color;

public:
	Rect area;

	ParrotContainer(Rect rect, Color color) : area(rect), color(color)
	{ }

	void draw()
	{
		area.draw(color);
	}
};