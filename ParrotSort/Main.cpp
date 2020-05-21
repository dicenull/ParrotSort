# include <Siv3D.hpp>

class Parrot
{
    Array<Image> parrots;
    const int size = 10;
    int index = 0;

public:
    Parrot(String path)
    {
        for (auto i : step(size))
        {
            parrots.push_back(Image(Format(path, i, ".png")));
        }
    }

    void next()
    {
        index = (index + 1) % size;
    }

    Image current()
    {
        return parrots[index];
    }
};

void Main()
{
    Parrot black(U"parrots/black"), pink(U"parrots/pink");

    const Point pos(10, 90);

    while (System::Update())
    {
        
    }
}