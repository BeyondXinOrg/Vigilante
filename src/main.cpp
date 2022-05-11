#include <QApplication>

#include "battle/warfare.h"

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    Battle warfare;
    warfare.BeginWar();

    return a.exec();
}
