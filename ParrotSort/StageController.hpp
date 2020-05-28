#pragma once
#include <Siv3D.hpp>

class StageController
{
	Stopwatch sw;
	int flip = 0;
	int count = 0;

	ParrotManager& manager;
	ParrotBuilder& builder;

	Point upPos, downPos;

public:
	bool isStart = false;
	bool gameover = false;

	int stage = 0;

public:
	StageController(ParrotManager& manager, ParrotBuilder& builder) 
		: manager(manager), builder(builder),
		  upPos(Scene::Width() / 2, 150), downPos(Scene::Width() / 2, Scene::Height() - 150){ }

	void start()
	{
		sw.start();
		isStart = true;
	}

	void update()
	{
		switch (stage)
		{
		case 0:
			if (sw.ms() > 2000)
			{
				generate(upPos);
			}

			if (count > 15)
			{
				next();
			}
			break;
		case 1:
			if (sw.ms() > 2000)
			{
				generate(flip ? upPos : downPos);
				flip = 1 - flip;
			}

			if (count > 20)
			{
				next();
			}
			break;
		case 2:
			if (sw.ms() > 2300)
			{
				auto& pos = flip ? upPos : downPos;
				for (auto i : step(2))
				{
					generate(pos + Point(-100 + (i + 1) * 50, 0));
				}
				flip = 1 - flip;
			}

			if (count > 20)
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

		count++;
		sw.restart();
	}

	void next()
	{
		stage++;
		count = 0;
	}
};