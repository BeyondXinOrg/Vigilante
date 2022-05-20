#include <QApplication>

#include "audios/audios_manager.h"
#include "battle/warfare.h"

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    Battle warfare;
    warfare.BeginWar();

    AudiosManager::Instance()->LoadBgMusic("战斗音乐.测试1", "./resource/audios/battle.mp3");
    AudiosManager::Instance()->PlayBg("战斗音乐.测试1");

    return a.exec();
}
