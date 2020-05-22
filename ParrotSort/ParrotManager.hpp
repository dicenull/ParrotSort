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

public:

	void generate(ParrotColor type)
	{
		Point point = Point(Scene::Width() / 2, 100);

		ParrotData& data = _default;
		if (type == ParrotColor::Pink)
		{
			data = _pink;
		}
		else if(type == ParrotColor::Black)
		{
			data = _black;
		}
			
		parrots.push_back(Parrot(point, data.parrotTextures));
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
		for (auto& parrot : parrots)
		{
			parrot.update();
		}
	}
};
