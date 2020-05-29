# include <Siv3D.hpp>
#include "Parrot.hpp"
#include "ParrotManager.hpp"
#include "ParrotBuilder.hpp"
#include "StageController.hpp"

// 1 TODO: continueができるように
// 2 TODO: 得点が入った時に少し止める
// 4 TODO: 上と下に扉を描画するようにする

void Main()
{
    // TODO: よりおおくのparrotを生成
    ParrotManager manager{};
    auto builder = ParrotBuilder();
    
    Scene::SetBackground(Palette::Gray);

    int sum = 0;

    const auto size = Size(200, 200);
    const auto padding = Point(10, 200);

    Array<ParrotContainer> containers;
    containers.push_back({ { padding, size }, ParrotColor::Pink });
    containers.push_back({ { Point(Scene::Width() - padding.x - size.x, padding.y), size }, ParrotColor::Black });

    StageController stageCon{manager, builder};

    Font mainFont{ 50 }, statFont{ 30 };

    while (System::Update())
    {
        if (!stageCon.isStart && KeySpace.down())
        {
            stageCon.start();
        }

        if (stageCon.isStart && !stageCon.gameover)
        {
            stageCon.update();

            int point = 0;
            for (auto& container : containers)
            {
                bool wrong = manager.checkArea(container);
                point += container.update();

                if (wrong)
                {
                    container.clear();
                    stageCon.gameover = true;
                }
            }
           
            stageCon.gameover |= manager.update();

            if (point > 0)
            {
                // TODO: 得点追加のアクション
                sum += point;
            }

            if (stageCon.gameover)
            {
                manager.gameover(builder.Default.parrotTextures);

                for (auto& container : containers)
                {
                    sum += container.count();
                }
            }
        }

        for (auto& container : containers)
        {
            container.draw();
        }
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