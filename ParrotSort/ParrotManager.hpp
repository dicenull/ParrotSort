#pragma once
#include <Siv3D.hpp>
#include "Parrot.hpp"
#include "ParrotData.hpp"
#include "ParrotColor.h"

class ParrotManager
{
	Array<Parrot> parrots;
	
	bool prev_hold = false;

public:
	void add(Parrot parrot)
	{
		parrots.push_back(parrot);
	}
	
	void draw()
	{
		for (auto& parrot : parrots)
		{
			parrot.draw();
		}
	}

	void update()
	{
		if (MouseL.up())
		{
			for (auto& parrot : parrots)
			{
				parrot.hold = false;
			}

			prev_hold = false;
		}

		for (auto& parrot : parrots)
		{
			parrot.update();

			if (!prev_hold && parrot.rect.leftClicked())
			{
				parrot.hold = true;
				prev_hold = true;
			}
		}
	}

	void checkArea(Rect rect)
	{
		for (auto& parrot : parrots)
		{
			if (rect.top().intersects(parrot.rect)
				|| rect.bottom().intersects(parrot.rect))
			{
				parrot.flipY();
			}

			if (rect.left().intersects(parrot.rect)
				|| rect.right().intersects(parrot.rect))
			{
				parrot.flipX();
			}
		}
	}
};
