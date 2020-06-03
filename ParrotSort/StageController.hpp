#pragma once
#include <Siv3D.hpp>
#include "ParrotToPointer.hpp"
#include "Consts.hpp"
#include "StageData.hpp"
#include "StageData.hpp"

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

	Array<StageData> stages;
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
		waveSw(), scoreSw()
	{
		stages.push_back({ 2000, 25, 1, 0 });
		stages.push_back({ 2000, 20, 1, 1 });
		stages.push_back({ 3000, 20, 2, 2 });
		stages.push_back({ 3000, 20, 2, 3 });
		stages.push_back({ 1000, 25, 1, 1 });
		stages.push_back({ 2800, 10000, 2, 2, true });
	}

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
			waveSw.restart();
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
		auto current = stages[stage];

		if (waveSw.ms() > current.timeMs)
		{
			int up = current.upCount;
			int down = current.downCount;

			if (!current.isSame)
			{
				if (flip) up = 0;
				else down = 0;
			}

			for (auto i : step(up))
			{
				generate(upPos + Point(-100 + (i + 1) * 50, 0));
			}
			for (auto i : step(down))
			{
				generate(downPos + Point(-100 + (i + 1) * 50, 0));
			}
			flip = 1 - flip;
		}

		if (wave > current.waveCount)
		{
			next();
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