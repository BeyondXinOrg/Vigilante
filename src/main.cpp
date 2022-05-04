#include <QApplication>

#include "battle_manager.h"

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    BattleManager battle;
    battle.Launch();

    return a.exec();
}
