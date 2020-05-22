#include <Siv3D.hpp>

class ParrotData
{
public:
    const int length = 10;
	Array<Texture> parrotTextures;

    ParrotData() {}

	ParrotData(String path)
    {
        for (auto i : step(length))
        {
            parrotTextures.push_back(Texture(Format(path, i, U".png")));
        }
    }

    ParrotData(const ParrotData& obj)
    {
        parrotTextures = obj.parrotTextures;
    }

    ParrotData& operator=(const ParrotData & obj)
    {
        parrotTextures = obj.parrotTextures;

        return *this;
    }
};