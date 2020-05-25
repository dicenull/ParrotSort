#pragma once
#include "ParrotData.hpp"
#include "ParrotColor.h"
#include "Parrot.hpp"

class ParrotBuilder
{
	ParrotBuilder() = default;
	ParrotData _pink = ParrotData(U"parrots/pink/pink");
	ParrotData _black = ParrotData(U"parrots/black/black");
	ParrotData _default = ParrotData(U"parrots/default/parrot");


public:
	static ParrotBuilder& instance()
	{
		static ParrotBuilder _instance;
		return _instance;
	}

	Parrot generate(ParrotColor type, Point pos)
	{
		switch (type)
		{
		case ParrotColor::Pink:
			return Parrot(pos, _pink.parrotTextures);
		case ParrotColor::Black:
			return Parrot(pos, _black.parrotTextures);
		case ParrotColor::Default:
			return Parrot(pos, _default.parrotTextures);
		}
	}

};