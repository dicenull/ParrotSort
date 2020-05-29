# include <Siv3D.hpp>
#include "Parrot.hpp"
#include "ParrotManager.hpp"
#include "ParrotBuilder.hpp"
#include "StageController.hpp"

// TODO: 当たり判定を少し小さくしてコンテナに入れやすく
// TODO: continueができるように
// TODO: 得点が入った時に少し止める
// TODO: ゲームオーバーの後、コンテナに残ったparrotを得点に追加
// TODO: 上と下に扉を描画するようにする

void Main()
{
    // TODO: よりおおくのparrotを生成
    ParrotManager manager{};
    auto builder = ParrotBuilder();
    
    Scene::SetBackground(Palette::Gray);

    int sum = 0;

    const auto size = Size(200, 200);
    const auto padding = Point(10, 200);
    ParrotContainer pink_container({ padding, size }, ParrotColor::Pink);
    ParrotContainer black_container({ Point(Scene::Width() - padding.x - size.x, padding.y), size }, ParrotColor::Black);

    StageController stageCon{manager, builder};

    Font mainFont{ 50 }, statFont{ 30 };

    while (System::Update())
    {
        if (KeySpace.down())
        {
            stageCon.start();
        }

        if (stageCon.isStart && !stageCon.gameover)
        {
            stageCon.update();

            bool wrong = false;
            wrong |= manager.checkArea(pink_container);
            wrong |= manager.checkArea(black_container);
            if (wrong)
            {
                stageCon.gameover = true;
            }

            stageCon.gameover |= manager.update();

            int point = 0;
            point += pink_container.update();
            point += black_container.update();

            if (point > 0)
            {
                // TODO: 得点追加のアクション
                sum += point;
            }

            if (stageCon.gameover)
            {
                manager.gameover(builder.Default.parrotTextures);
            }
        }

        pink_container.draw();
        black_container.draw();
        manager.draw();

        // 文字が後ろに隠れてしまうため、描画の後
        statFont(U"Point: ", sum).draw(Vec2::Zero());

        if (stageCon.gameover)
        {
            mainFont(U"Game Over!!").drawAt(Scene::CenterF());

            if (KeyEnter.down())
            {
                System::Exit();
            }
        }

        if (!stageCon.isStart)
        {
            mainFont(U"Press [Space] to start!!").drawAt(Scene::CenterF());
        }
    }
}