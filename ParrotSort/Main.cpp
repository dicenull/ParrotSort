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
    const int size = 10;
    int index = 0;
    Counter counter{ 6 };

public:
    Parrot(String path)
    {
        for (auto i : step(size))
        {
            parrots.push_back(Texture(Format(path, i, U".png")));
        }
    }

    void next()
    {
        counter.increment();

        if (counter.getRefresh())
        {
            index = (index + 1) % size;
        }
    }

    Texture current()
    {
        return parrots[index];
    }
};

void Main()
{
    Parrot black(U"parrots/black/black"), pink(U"parrots/pink/pink");

    const Point pos(10, 90);

    while (System::Update())
    {
        black.current().draw(pos);
        pink.current().draw(Point(100, 200));

        black.next();
        pink.next();
    }
}