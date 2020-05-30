#pragma once
#include <Siv3D.hpp>

struct SE : IEffect
{
    double delay;
    bool isPlayShot = false;
    Audio audio;

    SE(const Audio& audio, double delay)
        : delay(delay), audio(audio)
    {

    }

    bool update(double t) override
    {
        if (t >= delay)
        {
            if (isPlayShot)
            {
                return audio.isPlaying();
            }

            isPlayShot = true;
            audio.playOneShot();
        }

        return true;
    }
};
