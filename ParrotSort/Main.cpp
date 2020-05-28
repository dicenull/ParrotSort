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

    Point pos = Point(Scene::Width() / 2, 150);
    
    bool start = false;
    bool gameover = false;
    int flip = 0;
    int sum = 0;

    const auto size = Size(200, 200);
    const auto padding = Point(10, 200);
    ParrotContainer pink_container({ padding, size }, ParrotColor::Pink);
    ParrotContainer black_container({ Point(Scene::Width() - padding.x - size.x, padding.y), size }, ParrotColor::Black);

    Font mainFont{ 50 }, statFont{ 30 };

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
                manager.add(builder.generate((ParrotColor)Random(flip), pos));

                flip = 1 - flip;
                sw.restart();
            }

            bool wrong = false;
            wrong |= manager.checkArea(pink_container);
            wrong |= manager.checkArea(black_container);
            if (wrong)
            {
                gameover = true;
            }

            gameover |= manager.update();

            int point = 0;
            point += pink_container.update();
            point += black_container.update();

            if (point > 0)
            {
                // TODO: 得点追加のアクション
                sum += point;
            }

            if (gameover)
            {
                manager.gameover(builder.Default.parrotTextures);
            }
        }

        pink_container.draw();
        black_container.draw();
        manager.draw();

        // 文字が後ろに隠れてしまうため、描画の後
        statFont(U"Point: ", sum).draw(Vec2::Zero());

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
}