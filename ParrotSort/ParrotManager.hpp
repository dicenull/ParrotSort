#pragma once
#include <Siv3D.hpp>
#include "Parrot.hpp"
#include "ParrotData.hpp"
#include "ParrotColor.h"
#include "ParrotContainer.hpp"

class ParrotManager
{
	Array<Parrot> parrots;
	const Font font{ 16 };
	
	bool prev_hold = false;

	void clearHold()
	{
		for (auto& parrot : parrots)
		{
			parrot.hold = false;
		}

		prev_hold = false;
	}

public:
	void add(Parrot parrot)
	{
		parrots.push_back(parrot);
	}
	
	void draw()
	{
		for(auto i = 0;i < parrots.size();i++)
		// for (auto& parrot : parrots)
		{
			parrots[i].draw();
			font(i).draw(parrots[i].rect.pos);
		}
	}

	void update()
	{
		if (MouseL.up())
		{
			clearHold();
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

	void checkArea(ParrotContainer& container)
	{
		auto& area = container.area;
		
		// ‚Ô‚Â‚©‚Á‚Ä‚¢‚½‚ç”½“]
		for(auto& parrot : parrots)
		{
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

		for (auto it = parrots.begin(); it != parrots.end(); ++it)
		{
			if (MouseL.up() && area.contains(it->rect))
			{
				container.store(*it);
				parrots.erase(it);
				break;
			}
		}
	}
};
