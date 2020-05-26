#pragma once
#include <Siv3D.hpp>

class ParrotContainer
{
	Color color;
	Array<Parrot> parrots;

public:
	Rect area;

	ParrotContainer(Rect rect, Color color) : area(rect), color(color)
	{ }

	void draw()
	{
		area.draw(color);

		for (auto& parrot : parrots)
		{
			parrot.draw();	
		}
	}

	void update()
	{
		for (auto& parrot : parrots)
		{
			parrot.update();

			if (area.top().intersects(parrot.rect)
				|| area.bottom().intersects(parrot.rect))
			{
				parrot.flipY();
			}

			if (area.left().intersects(parrot.rect)
				|| area.right().intersects(parrot.rect))
			{
				parrot.flipX();
			}

		}
	}

	void store(const Parrot& parrot)
	{
		parrots.push_back(parrot);
		parrots[parrots.size() - 1].canHold = false;
	}
};