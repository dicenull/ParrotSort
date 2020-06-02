#pragma once
#include <Siv3D.hpp>
#include "Parrot.hpp"

class ParrotToPointer
{
	Array<Parrot> parrots;

public:

	void add(const Array<Parrot>& parrots)
	{
		this->parrots.append(parrots);
	}

	int size() const
	{
		return parrots.size();
	}

	void remove()
	{
		if (parrots.isEmpty())
		{
			return;
		}

		parrots.pop_back();
	}

	void draw()
	{
		for (auto& parrot : parrots)
		{
			parrot.draw();
		}
	}
};