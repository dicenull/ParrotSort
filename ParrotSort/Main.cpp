# include <Siv3D.hpp>
#include "Parrot.hpp"
#include "ParrotManager.hpp"


void Main()
{
    // TODO: よりおおくのparrotを生成
    ParrotManager manager{};
    
    Scene::SetBackground(Palette::Gray);

    for (auto i : step(100))
    {
        manager.generate(ParrotColor(Random(1)));
    }

    while (System::Update())
    {
        manager.draw();

        manager.update();
    }

    // TODO: parrotをしまっておく領域を追加
    // TODO: 40を超えたら計算
    // TODO: 爆発処理
}