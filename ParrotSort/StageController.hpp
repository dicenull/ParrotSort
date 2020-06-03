#pragma once
#include <Siv3D.hpp>
#include "ParrotToPointer.hpp"
#include "Consts.hpp"

class StageController
{
	Stopwatch waveSw, scoreSw;
	int flip = 0;
	int wave = 0;

	ParrotManager& manager;
	ParrotBuilder& builder;
	ParrotToPointer& pointer;

	int originForBuild = Consts::minHeight + Consts::normalSize / 2;
	Point upPos, downPos;

	bool isScoring = false;
	int tempPoint = 0;
public:
	bool isStart = false;
	bool gameover = false;
	
	int stage = 0;
	int pointSum = 0;

	constexpr bool inGame() { return isStart && !gameover && !isScoring; }

public:
	StageController(ParrotManager& manager, ParrotBuilder& builder, ParrotToPointer& pointer) 
		: manager(manager), builder(builder), pointer(pointer),
		upPos(Scene::Width() / 2, originForBuild), downPos(Scene::Width() / 2, Scene::Height() - originForBuild),
		waveSw(), scoreSw() { }

	void start()
	{
		if (isStart)
		{
			return;
		}

		waveSw.start();
		isStart = true;
	}

	void reset()
	{
		manager.reset();
		isStart = false;
		gameover = false;
		stage = 0;
		wave = 0;
		pointSum = 0;
		waveSw.reset();
	}

	void scoring()
	{
		if (!isScoring)
		{
			return;
		}

		if (scoreSw.ms() > 250)
		{
			pointSum++;
			pointer.remove();
			scoreSw.restart();
		}

		if (pointer.size() <= 0)
		{
			isScoring = false;
			manager.resume();
			scoreSw.reset();
		}
	}

	void setScoring(const Array<Parrot>& parrots)
	{
		pointer.add(parrots);
		isScoring = true;
		manager.pause();
		scoreSw.start();
	}

	void restart()
	{
		reset();
		start();
	}

	void update()
	{
		switch (stage)
		{
		case 0:
			if (waveSw.ms() > 2000)
			{
				generate(upPos);
			}

			if (wave > 15)
			{
				next();
			}
			break;
		case 1:
			if (waveSw.ms() > 2000 - (wave * 5))
			{
				generate(flip ? upPos : downPos);
				flip = 1 - flip;
			}

			if (wave > 20)
			{
				next();
			}
			break;
		case 2:
			if (waveSw.ms() > 3000)
			{
				auto& pos = flip ? upPos : downPos;
				for (auto i : step(2))
				{
					generate(pos + Point(-100 + (i + 1) * 50, 0));
				}
				flip = 1 - flip;
			}

			if (wave > 20)
			{
				next();
			}
			break;
		case 3:
			if (waveSw.ms() > 3000)
			{
				auto& pos = flip ? upPos : downPos;
				for (auto i : step(flip ? 2 : 3))
				{
					generate(pos + Point(-100 + (i + 1) * 50, 0));
				}
				flip = 1 - flip;
			}

			if (wave > 20)
			{
				next();
			}
			break;
		case 4:
			if (waveSw.ms() > 3000)
			{
				for (auto i : step(2))
				{
					generate(upPos + Point(-100 + (i + 1) * 50, 0));
				}
				for (auto i : step(2))
				{
					generate(downPos + Point(-100 + (i + 1) * 50, 0));
				}
				flip = 1 - flip;
			}

			if (wave > 20)
			{
				next();
			}
			break;
		case 5:
			if (waveSw.ms() > 1000 - wave)
			{
				generate(flip ? upPos : downPos);
				flip = 1 - flip;
			}

			if (wave > 20)
			{
				next();
			}
			break;
		}
		
	}
private:
	void generate(Point pos)
	{
		manager.add(builder.generate((ParrotColor)Random(1), pos));

		wave++;
		waveSw.restart();
	}

	void next()
	{
		stage++;
		wave = 0;
	}
};