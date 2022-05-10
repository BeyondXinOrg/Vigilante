#include <QApplication>

#include "warfare/warfare.h"

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    Warfare warfare;
    warfare.BeginWar();

    return a.exec();
}
