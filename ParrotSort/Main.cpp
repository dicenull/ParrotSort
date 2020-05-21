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
    const int size = 64;
    int index = 0;
    Counter counter{ 6 };
    
public:
    Vec2 pos;
    Vec2 velocity;


public:
    Parrot(String path, Point pos)
    {
        for (auto i : step(length))
        {
            parrots.push_back(Texture(Format(path, i, U".png")));
        }

        this->pos = pos;
        this->velocity = Vec2(Random(-1.0, 1.0), Random(-1.0, 1.0));
    }

    void update()
    {
        counter.increment();

        if (counter.getRefresh())
        {
            index = (index + 1) % length;
        }

        pos.moveBy(velocity * Scene::DeltaTime() * 300);


        if (pos.x <= 0 || pos.x + size >= Scene::Width())
        {
            velocity.x *= -1;
        }

        if (pos.y <= 0 || pos.y + size >= Scene::Height())
        {
            velocity.y *= -1;
        }
    }

    Texture current()
    {
        return parrots[index];
    }
};

void Main()
{
    Parrot black(U"parrots/black/black", RandomPoint(Scene::Rect())),
        pink(U"parrots/pink/pink", RandomPoint(Scene::Rect()));
    
    Scene::SetBackground(Palette::Gray);

    Point size{ 64, 64 };

    while (System::Update())
    {
        black.current().resized(size).draw(black.pos);
        pink.current().resized(size).draw(pink.pos);

        black.update();
        pink.update();
    }
}