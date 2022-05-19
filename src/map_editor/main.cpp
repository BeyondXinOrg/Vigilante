#include <QApplication>

#include "main_window.h"

int main(int argc, char** argv)
{
    QApplication m_app(argc, argv);

    MainWindow* m_mainWindow = new MainWindow();
    m_mainWindow->showMaximized();

    return m_app.exec();
}
