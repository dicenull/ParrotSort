#pragma once
#include <Siv3D.hpp>

class ParrotContainer
{
	Color color;
	Array<Parrot> parrots;
	const int size = 20;

public:
	Rect area;
	ParrotColor colorType;

	ParrotContainer(Rect rect, ParrotColor type) : area(rect), colorType(type)
	{
		switch (type)
		{
		case ParrotColor::Pink:
			color = Palette::Pink;
			break;
		case ParrotColor::Black:
			color = Palette::Darkgray;
			break;
		case ParrotColor::Default:
			color = Palette::White;
			break;
		}
	}

	void clear()
	{
		parrots.clear();
	}

	int count()
	{
		return parrots.size();
	}

	void draw()
	{
		area.draw(color);

		for (auto& parrot : parrots)
		{
			parrot.draw();	
		}
	}

	int update()
	{
		if (parrots.size() >= size)
		{
			parrots.clear();

			return size;
		}

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

		return 0;
	}

	void store(const Parrot& parrot)
	{
		parrots.push_back(parrot);
		parrots[parrots.size() - 1].canHold = false;

		AudioAsset(U"ok").playOneShot();
	}
};