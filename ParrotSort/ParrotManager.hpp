#pragma once
#include <Siv3D.hpp>
#include "Parrot.hpp"
#include "ParrotData.hpp"
#include "ParrotColor.h"
#include "ParrotContainer.hpp"

class ParrotManager
{
	Array<Parrot> parrots;
	
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
	void reset()
	{
		parrots.clear();
		prev_hold = false;
	}

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

	void pause()
	{
		for (auto& parrot : parrots)
		{
			parrot.pause();
		}
	}

	void resume()
	{
		for (auto& parrot : parrots)
		{
			parrot.resume();
		}
	}

	bool update()
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

			if (parrot.isBomb)
			{
				return true;
			}
		}

		return false;
	}

	void gameover(Array<Texture> rainbows)
	{
		for (auto& parrot : parrots)
		{
			parrot.changeTexture(rainbows);
			parrot.changeSpeedRandom();
		}
	}

	bool checkArea(ParrotContainer& container)
	{
		auto& area = container.area;
		
		// ‚Ô‚Â‚©‚Á‚Ä‚¢‚½‚ç”½“]
		for(auto& parrot : parrots)
		{
			if (parrot.hold)
			{
				continue;
			}

			if(area.contains(parrot.rect.br()) 
				|| area.contains(parrot.rect.bl()))
			{
				parrot.lookUp();
			}

			if (area.contains(parrot.rect.bl())
				|| area.contains(parrot.rect.tl()))
			{
				parrot.lookRight();
			}
			
			if (area.contains(parrot.rect.tl())
				|| area.contains(parrot.rect.tr()))
			{
				parrot.lookDown();
			}

			if (area.contains(parrot.rect.tr())
				|| area.contains(parrot.rect.br()))
			{
				parrot.lookLeft();
			}
		}

		// ’†‚Å—£‚³‚ê‚½‚çŠi”[
		for (auto it = parrots.begin(); it != parrots.end(); ++it)
		{
			if (MouseL.up() && area.contains(it->paddingRect()))
			{
				if (it->colorType != container.colorType)
				{
					return true;
				}

				it->caught();
				container.store(*it);
				parrots.erase(it);
				break;
			}
		}

		return false;
	}
};
