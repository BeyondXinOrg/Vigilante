#include "main_window.h"
#include "ui_main_window.h"

#include "mediator.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <QSettings>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , mediator_(new Mediator(*this))
{
    ui->setupUi(this);
    setWindowTitle("Vigilate Map Editor");

    resize(QSize(1920, 1080));
    mediator_->InitScene();

    PopulateMenuBar();

    AddNewMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddCenterWidget(QWidget* wid)
{
    if (wid) {
        ui->lay_view->addWidget(wid);
    }
}

void MainWindow::PopulateMenuBar()
{
    // ---------------file menu---------------
    QMenu* file_menu = menuBar()->addMenu(tr("&File"));

    QAction* quit_act = new QAction(tr("&Quit"), this);
    quit_act->setShortcut(QKeySequence("Ctrl+W"));
    file_menu->addAction(quit_act);
    connect(quit_act, &QAction::triggered, this, &MainWindow::close);

    // ---------------edit menu---------------
    QMenu* edit_menu = menuBar()->addMenu(tr("&Edit"));
}

void MainWindow::AddNewMap()
{
    mediator_->CreateNewMap();
    QApplication::restoreOverrideCursor();
}
