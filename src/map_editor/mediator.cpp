#include "mediator.h"

#include "cell_grid.h"
#include "editor_data.h"
#include "editor_view.h"
#include "main_window.h"

#include <QGraphicsPixmapItem>

Mediator::Mediator(MainWindow& mainWindow)
  : main_window_(mainWindow)
  , editor_view_(new EditorView(&main_window_))
  , editor_scene_(new QGraphicsScene)
{
    cell_grid_ = new CellGrid(20, 18);
    editor_data_ = new EditorData(*this, cell_grid_, 128);
}

void Mediator::InitScene()
{
    editor_view_->setScene(editor_scene_);
    editor_view_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    editor_view_->setMouseTracking(true);

    main_window_.SetCenterWidget(editor_view_);
}

void Mediator::CreateNewMap()
{
    delete editor_scene_;
    editor_scene_ = new QGraphicsScene;

    editor_view_->setScene(editor_scene_);
    editor_view_->UpdateSceneRect();
    ResetSceneBackGround();

    QGraphicsPixmapItem* pixitem = new QGraphicsPixmapItem();
    QPixmap pix(u8"D:\\游戏资源\\美术\\地图\\曹操传地图\\MAP\\M002.jpg");
    pixitem->setPixmap(pix.scaled(128 * 20, 128 * 18));
    pixitem->setPos(0, 0);
    pixitem->setZValue(0);
    editor_scene_->addItem(pixitem);

    editor_data_->AddTileTypesToScene();
}

void Mediator::AddTileTypeItem(QGraphicsItem* item)
{
    item->setZValue(10);
    editor_scene_->addItem(item);
}

void Mediator::ResetSceneBackGround()
{
    if (editor_scene_) {
        QBrush bb;
        bb.setStyle(Qt::SolidPattern);
        bb.setColor(QColor(160, 160, 160));
        editor_scene_->setBackgroundBrush(bb);
    }
}
