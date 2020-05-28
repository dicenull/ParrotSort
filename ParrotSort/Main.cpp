# include <Siv3D.hpp>
#include "Parrot.hpp"
#include "ParrotManager.hpp"
#include "ParrotBuilder.hpp"


void Main()
{
    // TODO: よりおおくのparrotを生成
    ParrotManager manager{};
    Stopwatch sw;
    auto builder = ParrotBuilder();
    
    Scene::SetBackground(Palette::Gray);

    Point point = Point(Scene::Width() / 2, 150);
    
    bool start = false;
    bool gameover = false;
    int flip = 0;

    const auto size = Size(200, 200);
    const auto padding = Point(10, 200);
    ParrotContainer pink_container({ padding, size }, Palette::Pink);
    ParrotContainer black_container({ Point(Scene::Width() - padding.x - size.x, padding.y), size }, Palette::Darkgray);

    Font mainFont{ 50 };

    while (System::Update())
    {
        if (KeySpace.down())
        {
            start = true;
            sw.start();
        }

        if (start && !gameover)
        {
            if (sw.ms() >= 2000)
            {
                manager.add(builder.generate((ParrotColor)Random(flip), point));

                flip = 1 - flip;
                sw.restart();
            }

            manager.checkArea(pink_container);
            manager.checkArea(black_container);

            gameover = manager.update();
            pink_container.update();
            black_container.update();
        }

        pink_container.draw();
        black_container.draw();
        manager.draw();

        // 文字が後ろに隠れてしまうため、描画の後
        if (gameover)
        {
            mainFont(U"Game Over!!").drawAt(Scene::CenterF());

            if (KeyEnter.down())
            {
                System::Exit();
            }
        }

        if (!start)
        {
            mainFont(U"Press [Space] to start!!").drawAt(Scene::CenterF());
        }
    }

    // TODO: parrotをしまっておく領域を追加
    // TODO: 40を超えたら計算
    // TODO: 爆発処理
}