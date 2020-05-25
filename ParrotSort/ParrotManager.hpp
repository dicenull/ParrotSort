#pragma once
#include <Siv3D.hpp>
#include "Parrot.hpp"
#include "ParrotData.hpp"
#include "ParrotColor.h"

class ParrotManager
{
	Array<Parrot> parrots;
	ParrotData _pink = ParrotData(U"parrots/pink/pink");
	ParrotData _black = ParrotData(U"parrots/black/black");
	ParrotData _default = ParrotData(U"parrots/default/parrot");

	bool prev_hold = false;

public:

	void generate(ParrotColor type)
	{
		Point point = Point(Random(Scene::Width()), Random(Scene::Height())) - Point(32, 32);

		// Point point = Point(Scene::Width() / 2, 100);

		switch (type)
		{
		case ParrotColor::Pink:
			parrots.push_back(Parrot(point, _pink.parrotTextures));
			break;
		case ParrotColor::Black:
			parrots.push_back(Parrot(point, _black.parrotTextures));
			break;
		case ParrotColor::Default:
			parrots.push_back(Parrot(point, _default.parrotTextures));
			break;
		}
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
