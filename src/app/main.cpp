#include <QApplication>

#include "audios/audios_manager.h"
#include "battle/battle.h"
#include "battle/generate_battle.h"

#include "iostream"

int main(int argc, char* argv[])
{
    {
        char string[10];
        char* str1 = "0123456789";
        std::strcpy(string, str1);
        qDebug() << *string << *str1;
    }
    QApplication a(argc, argv);

    GenerateBattle factory;
    auto warfare = factory.GetBattle();
    warfare->BeginWar();

    return a.exec();
}
