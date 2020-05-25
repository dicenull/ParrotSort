# include <Siv3D.hpp>
#include "Parrot.hpp"
#include "ParrotManager.hpp"
#include "ParrotBuilder.cpp"


void Main()
{
    // TODO: よりおおくのparrotを生成
    ParrotManager manager{};
    auto builder = ParrotBuilder::instance();
    
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
    Rect pink_area{ padding, size };
    Rect black_area{ Point(Scene::Width() - padding.x - size.x, padding.y), size };

    while (System::Update())
    {
        if (KeySpace.down())
        {
            start = true;
        }

        if (start)
        {
            pink_area.draw(Palette::Pink);
            black_area.draw(Palette::Darkgray);

            manager.draw();

            manager.update();

            manager.checkArea(pink_area);
            manager.checkArea(black_area);
        }
    }

    // TODO: parrotをしまっておく領域を追加
    // TODO: 40を超えたら計算
    // TODO: 爆発処理
}