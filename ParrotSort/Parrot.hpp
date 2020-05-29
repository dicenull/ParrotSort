#pragma once
#include "Counter.hpp"
#include "ParrotData.hpp"
#include "ParrotColor.h"

class Parrot
{
    static int serial_gen;

    int index = 0;
    int speed = 50;
    int normalSize = 55;
    
    Counter counter{ 6 };
    Array<Texture> textures;

    Vec2 velocity;

    Stopwatch dangerSw;
    bool isNormal = true;

public:
    RectF drawingRect;
    bool hold = false;
    bool canHold = true;
    bool isBomb = false;
    int serial;

    ParrotColor colorType;

public:
    Parrot() : serial(serial_gen++) {}

    Parrot(Point pos, Array<Texture> textures, ParrotColor type)
        : drawingRect(RectF(pos, normalSize)),
        textures(textures),
        colorType(type),
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

    constexpr RectF paddingRect() const
    {
        return drawingRect.scaled(0.65);
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

    void caught()
    {
        dangerSw.reset();
        drawingRect.setSize(normalSize);

        if (!isNormal)
        {
            isNormal = true;
        }
    }

    void changeTexture(Array<Texture> newTex)
    {
        textures = newTex;
    }

    void changeSpeedRandom()
    {
        counter = Counter(Random(6));
    }

    void update()
    {
        if(isNormal && dangerSw.s() > 5)
        {
            isNormal = false;
        }

        if (!isNormal && dangerSw.s() > 10)
        {
            isBomb = true;
        }

        if (!isNormal)
        {
            drawingRect.setSize(normalSize + 30 * Periodic::Sine0_1(500ms));
        }

        if (canHold && hold)
        {
            drawingRect.pos = Cursor::Pos() - drawingRect.size / 2;
        }
        else
        {
            drawingRect.pos.moveBy(velocity * Scene::DeltaTime() * speed);
        }

        bool isLeft = drawingRect.tl().x <= 0,
            isRight = drawingRect.br().x >= Scene::Width(),
            isTop = drawingRect.tl().y <= 0,
            isBottom = drawingRect.br().y >= Scene::Height();

        if (canHold && hold)
        {
            if (isLeft) drawingRect.pos.x = 1;
            if (isTop) drawingRect.pos.y = 1;

            if (isRight) drawingRect.pos.x = Scene::Width() - drawingRect.size.x - 1;
            if (isBottom) drawingRect.pos.y = Scene::Height() - drawingRect.size.y - 1;
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

        paddingRect().drawFrame();
    }

    void draw()
    {
        counter.increment();

        if (counter.isRefresh())
        {
            index = (index + 1) % textures.size();
        }

        drawingRect(textures[index]).draw();
    }
};
