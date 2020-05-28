#pragma once
#include "Counter.hpp"
#include "ParrotData.hpp"
#include "ParrotColor.h"

class Parrot
{
    static int serial_gen;

    int index = 0;
    int speed = 50;
    
    Counter counter{ 6 };
    Array<Texture> textures, rainbows;
    Vec2 velocity;

    Stopwatch dangerSw;
    bool isNormal = true;

public:
    RectF rect;
    bool hold = false;
    bool canHold = true;
    bool isBomb = false;
    int serial;

public:
    Parrot() : serial(serial_gen++) {}

    Parrot(Point pos, Array<Texture> textures)
        : Parrot(pos, textures, textures) { }

    Parrot(Point pos, Array<Texture> textures, Array<Texture> rainbows)
        : rect(RectF(pos, 64)),
        textures(textures),
        rainbows(rainbows),
        serial(serial_gen++)
    {
        auto rnd_rad = ToRadians(Random(360));
        velocity = Vec2(Math::Cos(rnd_rad), Math::Sin(rnd_rad));

        dangerSw.start();
    }
    
    ~Parrot()
    {
        for (auto& tex : textures)
        {
            tex.release();
        }
    }

    bool operator==(const Parrot& obj)
    {
        return obj.serial == serial;
    }

    void flipY()
    {
        velocity.y *= -1;
    }

    void flipX()
    {
        velocity.x *= -1;
    }

    void update()
    {
        if(isNormal && dangerSw.s() > 5)
        {
            textures.swap(rainbows);
            isNormal = false;
        }

        if (!isNormal && dangerSw.s() > 10)
        {
            isBomb = true;
        }

        counter.increment();

        if (counter.isRefresh())
        {
            index = (index + 1) % textures.size();
        }

        if (canHold && hold)
        {
            rect.pos = Cursor::Pos() - rect.size / 2;
        }
        else
        {
            rect.pos.moveBy(velocity * Scene::DeltaTime() * speed);
        }

        bool isLeft = rect.tl().x <= 0,
            isRight = rect.br().x >= Scene::Width(),
            isTop = rect.tl().y <= 0,
            isBottom = rect.br().y >= Scene::Height();

        if (canHold && hold)
        {
            if (isLeft) rect.pos.x = 1;
            if (isTop) rect.pos.y = 1;

            if (isRight) rect.pos.x = Scene::Width() - rect.size.x - 1;
            if (isBottom) rect.pos.y = Scene::Height() - rect.size.y - 1;
        }
        else
        {
            if (isLeft || isRight)
            {
                flipX();
            }

            if (isTop || isBottom)
            {
                flipY();
            }
        }


        // TODO: debug
        rect.drawFrame();
    }

    void draw()
    {
        rect(textures[index]).draw();
    }
};
