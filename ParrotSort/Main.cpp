# include <Siv3D.hpp>
#include "Parrot.hpp"
#include "ParrotManager.hpp"


void Main()
{
    // TODO: よりおおくのparrotを生成
    ParrotManager manager{};
    
    Scene::SetBackground(Palette::Gray);

    
    manager.generate(ParrotColor::Default);
    for (auto i : step(100))
    {
        manager.generate(ParrotColor(Random(1)));
    }
    
    bool start = false;

    while (System::Update())
    {
        if (start)
        {
            manager.draw();

            manager.update();
        }

        if (KeySpace.down())
        {
            start = true;
        }
    }

    // TODO: parrotをしまっておく領域を追加
    // TODO: 40を超えたら計算
    // TODO: 爆発処理
}