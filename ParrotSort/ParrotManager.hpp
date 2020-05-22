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

public:

	void generate(ParrotColor type)
	{
		Parrot newParrot;
		Point point = RandomPoint(Scene::Rect());

		parrots.push_back(Parrot(point, type));
	}

	void draw()
	{
		for (auto& parrot : parrots)
		{
			ParrotData data;
			if (parrot.colorType == ParrotColor::Pink)
			{
				data = _pink;
			}
			else
			{
				data = _black;
			}

			parrot.rect(data.parrotTextures[parrot.current()]).draw();
		}
	}

	void update()
	{
		for (auto& parrot : parrots)
		{
			parrot.update();
		}
	}
};
