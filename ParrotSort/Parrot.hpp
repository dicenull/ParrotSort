#pragma once
#include "Counter.hpp"
#include "ParrotData.hpp"
#include "ParrotColor.h"
#include "Consts.hpp"

class Parrot
{
    static int serial_gen;

    int index = 0;
    int speed = 50;
    
    Counter counter{ 6 };
    Array<Texture> textures;

    Vec2 velocity;

    Stopwatch dangerSw;
    bool isNormal = true;

public:
    RectF rect;
    bool hold = false;
    bool canHold = true;
    bool isBomb = false;
    int serial;

    ParrotColor colorType;

public:
    Parrot() : serial(serial_gen++) {}

    Parrot(Point pos, Array<Texture> textures, ParrotColor type)
        : rect(RectF(Arg::center = pos, Consts::normalSize)),
        textures(textures),
        colorType(type),
        serial(serial_gen++)
    {
        auto rndDeg = Random(180);
        // ’†‰›‘¤‚ðŒü‚­•ûŒü‚ðÝ’è
        if (pos.y * 2 > Scene::Height())
        {
            rndDeg += 180;
        }

        auto rad = ToRadians(rndDeg);
        velocity = Vec2(Math::Cos(rad), Math::Sin(rad));

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
        return RectF(Arg::center = rect.center(), Vec2(0.65, 0.65) * Consts::normalSize);
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

    void lookUp()
    {
        velocity.y = -Math::Abs(velocity.y);
    }

    void lookDown()
    {
        velocity.y = Math::Abs(velocity.y);
    }

    void lookLeft()
    {
        velocity.x = -Math::Abs(velocity.x);
    }

    void lookRight()
    {
        velocity.x = Math::Abs(velocity.x);
    }

    void caught()
    {
        dangerSw.reset();
        rect.setSize(Consts::normalSize);

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
        counter = Counter(Random(5) + 1);
    }

    void pause()
    {
        dangerSw.pause();
    }

    void resume()
    {
        dangerSw.resume();
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
            rect.setSize(Consts::normalSize + 30 * Periodic::Sine0_1(500ms));
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
            isTop = rect.tl().y <= Consts::minHeight,
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

        // Debug
        // paddingRect().drawFrame();
        // rect.drawFrame();
    }

    void draw()
    {
        if (textures.size() == 0)
        {
            return;
        }

        counter.increment();

        if (counter.isRefresh())
        {
            index = (index + 1) % textures.size();
        }

        rect(textures[index]).draw();
    }
};
