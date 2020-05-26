# include <Siv3D.hpp>
#include "Parrot.hpp"
#include "ParrotManager.hpp"
#include "ParrotBuilder.hpp"


void Main()
{
    // TODO: よりおおくのparrotを生成
    ParrotManager manager{};
    auto builder = ParrotBuilder();
    
    Scene::SetBackground(Palette::Gray);

    Point point = Point(Scene::Width() / 2, 150);
    
    manager.add(builder.generate(ParrotColor::Default, point));
    for (auto i : step(10))
    {
        manager.add(builder.generate(ParrotColor(Random(1)), point));
    }

    bool start = false;

    const auto size = Size(200, 200);
    const auto padding = Point(10, 200);
    ParrotContainer pink_container({ padding, size }, Palette::Pink);
    ParrotContainer black_container({ Point(Scene::Width() - padding.x - size.x, padding.y), size }, Palette::Darkgray);

    while (System::Update())
    {
        if (KeySpace.down())
        {
            start = true;
        }

        if (start)
        {
            pink_container.draw();
            black_container.draw();
            
            manager.draw();

            manager.checkArea(pink_container);
            manager.checkArea(black_container);
            manager.update();
        }
    }

    // TODO: parrotをしまっておく領域を追加
    // TODO: 40を超えたら計算
    // TODO: 爆発処理
}