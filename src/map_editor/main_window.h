#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class Mediator;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void AddCenterWidget(QWidget* wid);

private:
    void PopulateMenuBar();
    void AddNewMap();

private:
    Ui::MainWindow* ui;

    Mediator* mediator_;
};

#endif // MAIN_WINDOW_H
