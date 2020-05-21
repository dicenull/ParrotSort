# include <Siv3D.hpp>

class Counter
{
    int count, max;
    bool refresh = false;

public:
    Counter(int max)
    {
        this->max = max;
    }

    void increment()
    {
        count++;
        count %= max;

        refresh = (count == 0);
    }

    bool getRefresh() { return refresh; }
};

class Parrot
{
    Array<Texture> parrots;
    const int length = 10;
    int index = 0;
    Counter counter{ 6 };
    
public:
    Vec2 velocity;
    RectF rect;


public:
    Parrot(String path, Point pos)
    {
        for (auto i : step(length))
        {
            parrots.push_back(Texture(Format(path, i, U".png")));
        }

        rect = RectF(pos, 64);
        this->velocity = Vec2(Random(-1.0, 1.0), Random(-1.0, 1.0));
    }

    void update()
    {
        counter.increment();

        if (counter.getRefresh())
        {
            index = (index + 1) % length;
        }

        // TODO: parrotが重なるとどちらもつかめてしまう
        if (rect.leftPressed())
        {
            rect.pos = Cursor::Pos() - rect.size / 2;
        }
        else
        {
            rect.pos.moveBy(velocity * Scene::DeltaTime() * 100);
        }

        bool isLeft = rect.tl().x <= 0,
            isRight = rect.br().x >= Scene::Width(),
            isTop = rect.tl().y <= 0,
            isBottom = rect.br().y >= Scene::Height();
 

        if (rect.leftPressed())
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
                velocity.x *= -1;

            }

            if (isTop || isBottom)
            {
                velocity.y *= -1;
            }
        }

        rect.drawFrame();
    }

    Texture current()
    {
        return parrots[index];
    }
};

void Main()
{
    // TODO: よりおおくのparrotを生成
    Parrot black(U"parrots/black/black", RandomPoint(Scene::Rect())),
        pink(U"parrots/pink/pink", RandomPoint(Scene::Rect()));
    
    Scene::SetBackground(Palette::Gray);

    while (System::Update())
    {
        black.rect(black.current()).draw();
        pink.rect(pink.current()).draw();
        
        black.update();
        pink.update();
    }

    // TODO: parrotをしまっておく領域を追加
    // TODO: 40を超えたら計算
    // TODO: 爆発処理
}