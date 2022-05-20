#include <QApplication>

#include "audios/audios_manager.h"
#include "battle/generate_battle.h".h "
#include "battle/warfare.h"

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    GenerateBattle factory;
    auto warfare = factory.GetBattle();
    warfare->BeginWar();

    return a.exec();
}
