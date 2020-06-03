#pragma once

struct StageData
{
	int timeMs;
	int waveCount;
	int upCount, downCount;
	bool isSame = false;

	constexpr bool isNext(int wave) { return wave > waveCount; }

	StageData(int ms, int wave, int up, int down, bool same = false)
		: timeMs(ms), waveCount(wave), upCount(up), downCount(down), isSame(same) {}
};
