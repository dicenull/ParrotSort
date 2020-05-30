#pragma once
#include <Siv3D.hpp>

class StageController
{
	Stopwatch waveSw, scoreSw;
	int flip = 0;
	int wave = 0;

	ParrotManager& manager;
	ParrotBuilder& builder;

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
	StageController(ParrotManager& manager, ParrotBuilder& builder) 
		: manager(manager), builder(builder),
		upPos(Scene::Width() / 2, 150), downPos(Scene::Width() / 2, Scene::Height() - 150),
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
		Print << U"score";

		if (scoreSw.ms() > 250)
		{
			Print << tempPoint;
			pointSum++;
			tempPoint--;
			scoreSw.restart();
		}

		if (tempPoint <= 0)
		{
			isScoring = false;
			scoreSw.reset();
		}
	}

	void setScoring(int point)
	{
		tempPoint = point;
		isScoring = true;
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
			if (waveSw.ms() > 2000)
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
			if (waveSw.ms() > 2300)
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
			if (waveSw.ms() > 1000)
			{
				generate(flip ? upPos : downPos);
				flip = 1 - flip;
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