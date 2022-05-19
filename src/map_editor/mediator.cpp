#include "mediator.h"

#include "cell_grid.h"
#include "editor_data.h"
#include "editor_view.h"
#include "main_window.h"
#include "tool_widget.h"

#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

Mediator::Mediator(MainWindow& mainWindow)
  : main_window_(mainWindow)
  , tool_wid_(new ToolWidget)
  , editor_view_(new EditorView(this, &main_window_))
  , editor_scene_(new QGraphicsScene)
  , lay_bg_(new QGraphicsRectItem())
{
    cell_grid_ = new CellGrid(20, 18);
    editor_data_ = new EditorData(*this, cell_grid_, 128);
}

void Mediator::InitScene()
{
    editor_view_->setScene(editor_scene_);
    editor_view_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    editor_view_->setMouseTracking(true);
    editor_scene_->addItem(lay_bg_);

    main_window_.AddCenterWidget(editor_view_);
    main_window_.AddCenterWidget(tool_wid_);
}

void Mediator::CreateNewMap()
{
    editor_scene_->removeItem(lay_bg_);
    delete editor_scene_;
    editor_scene_ = new QGraphicsScene;
    editor_scene_->addItem(lay_bg_);

    editor_view_->setScene(editor_scene_);
    editor_view_->UpdateSceneRect();
    ResetSceneBackGround();

    QGraphicsPixmapItem* pixitem = new QGraphicsPixmapItem();
    QPixmap pix(u8"D:\\游戏资源\\美术\\地图\\曹操传地图\\MAP\\M002.jpg");
    pixitem->setPixmap(pix.scaled(128 * 20, 128 * 18));
    pixitem->setPos(0, 0);
    pixitem->setZValue(0);

    pixitem->setParentItem(lay_bg_);

    editor_data_->AddTileTypesToScene();
}

void Mediator::AddTileTypeItem(QGraphicsItem* item)
{
    item->setZValue(10);
    item->setParentItem(lay_bg_);
}

// 处理鼠标按下
void Mediator::MousePress(QMouseEvent* event)
{
    auto mouse_buttons = QApplication::mouseButtons();
    if (mouse_buttons & Qt::MiddleButton) { // 只下发中键拦截
        prev_mid_mouse_pos_ = event->pos();
    } else {
    }
}

// 处理鼠标移动
void Mediator::MouseMove(QMouseEvent* event)
{
    auto mouse_buttons = QApplication::mouseButtons();

    if (mouse_buttons & Qt::MiddleButton) { // 鼠标中键,移动画布
        editor_view_->setDragMode(QGraphicsView::NoDrag);
        editor_scene_->clearSelection();
        if (editor_scene_->mouseGrabberItem()) {
            editor_scene_->mouseGrabberItem()->ungrabMouse();
        }

        QPointF delta_pos = event->pos() - prev_mid_mouse_pos_;
        MoveBgLayout(delta_pos);
        prev_mid_mouse_pos_ = event->pos();
    } else { // 鼠标移动时无按键
    }

    event->accept();
}

// 处理鼠标松开
void Mediator::MouseRelease(QMouseEvent* event)
{
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

void Mediator::MoveBgLayout(const QPointF& delta)
{
    lay_bg_->setPos(lay_bg_->pos() + delta);
}
