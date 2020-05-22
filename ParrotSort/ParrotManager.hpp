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
		Point point = Point(Scene::Width() / 2, 100);
			
		parrots.push_back(Parrot(point, type == ParrotColor::Pink 
			? _pink.parrotTextures 
			: _black.parrotTextures));
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
