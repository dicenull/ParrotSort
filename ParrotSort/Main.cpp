# include <Siv3D.hpp>
#include "Parrot.hpp"
#include "ParrotManager.hpp"
#include "ParrotBuilder.hpp"
#include "StageController.hpp"
#include "SoundEffect.hpp"

// TODO: 得点が入った時に少し止める
// TODO: 上と下に扉を描画するようにする
// TODO: SEの追加 OK, Oh... 

void Main()
{
    AudioAsset::Register(U"ok", U"se/OK.mp3");
    AudioAsset::Register(U"oh", U"se/Oh.mp3");

    Effect effects;

    // TODO: よりおおくのparrotを生成
    ParrotManager manager{};
    auto builder = ParrotBuilder();
    
    Scene::SetBackground(Palette::Gray);

    const auto size = Size(200, 200);
    const auto padding = Point(10, 200);

    Array<ParrotContainer> containers;
    containers.push_back({ { padding, size }, ParrotColor::Pink });
    containers.push_back({ { Point(Scene::Width() - padding.x - size.x, padding.y), size }, ParrotColor::Black });

    StageController stageCon{manager, builder};

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
                for (auto i : step(point))
                {
                    effects.add<SE>(AudioAsset(U"ok"), Random());
                }
                stageCon.setScoring(point);
            }

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
        for (auto& container : containers)
        {
            container.draw();
        }
        manager.draw();

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