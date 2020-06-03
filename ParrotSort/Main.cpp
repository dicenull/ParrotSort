# include <Siv3D.hpp>
#include "Parrot.hpp"
#include "ParrotManager.hpp"
#include "ParrotBuilder.hpp"
#include "StageController.hpp"
#include "SoundEffect.hpp"
#include "Consts.hpp"

// TODO: 上と下に扉を描画するようにする

void Main()
{
    AudioAsset::Register(U"ok", U"se/OK.mp3");
    AudioAsset::Register(U"oh", U"se/Oh.mp3");

    const auto size = Size(200, 200);
    const auto padding = Point(10, 200);


    Effect effects;

    ParrotManager manager{};
    ParrotBuilder builder{};
    
    Scene::SetBackground(Palette::Gray);
    Rect ground{ Point(padding.x, Consts::minHeight), Scene::Size() - Size(padding.x, Consts::minHeight) * 2 };
    Line divideLine{ Point(0, Consts::minHeight), Point(Scene::Width(), Consts::minHeight) };

    Array<ParrotContainer> containers;
    containers.push_back({ { padding, size }, ParrotColor::Pink });
    containers.push_back({ { Point(Scene::Width() - padding.x - size.x, padding.y), size }, ParrotColor::Black });

    ParrotToPointer pointer{};

    StageController stageCon{manager, builder, pointer};

    Font mainFont{ 50 }, statFont{ 30 };

    while (System::Update())
    {
        // 更新
        effects.update();

        if (KeyEnter.down())
        {
            stageCon.start();
        }

        stageCon.scoring();

        if (stageCon.inGame())
        {
            stageCon.update();

            for (auto& container : containers)
            {
                bool wrong = manager.checkArea(container);
                int point = container.update();

                if (wrong)
                {
                    container.clear();
                    stageCon.gameover = true;
                }

                if (point > 0)
                {
                    stageCon.setScoring(container.shipParrot());

                    // TODO: 得点追加のアクション
                    for (auto i : step(point))
                    {
                        effects.add<SE>(AudioAsset(U"ok"), Random());
                    }
                }
            }
           
            stageCon.gameover |= manager.update();

            if (stageCon.gameover)
            {
                manager.gameover(builder.Default.parrotTextures);

                for (auto& container : containers)
                {
                    stageCon.pointSum += container.count();
                }

                AudioAsset(U"oh").playOneShot();
            }
        }

        // 描画
        ground.draw(Palette::Lightgrey);
        for (auto& container : containers)
        {
            container.draw();
        }
        manager.draw();
        pointer.draw();
        divideLine.draw(2.5, Palette::Black);

        // 文字が後ろに隠れてしまうため、後に描画
        statFont(U"Point: ", stageCon.pointSum).draw(Vec2::Zero());

        if (stageCon.gameover)
        {
            mainFont(U"Game Over!!\n[Enter] to restart!").drawAt(Scene::CenterF());

            if (KeyEnter.down())
            {
                containers.each([](ParrotContainer& con) {con.clear(); });
                stageCon.restart();
            }
        }

        if (!stageCon.isStart)
        {
            mainFont(U"Press [Enter] to start!!").drawAt(Scene::CenterF());
        }
    }
}