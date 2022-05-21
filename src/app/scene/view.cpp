#include "view.h"

#include "data/cell_grid.h"
#include "gui/gui.h"
#include "scene/path_grid.h"
#include "scene/scene_manager.h"

#include <QDebug>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>

View::View(QWidget* parent)
  : QGraphicsView(parent)
{
    // 禁用QGraphicsView的滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 追踪鼠标
    //    setMouseTracking(true);

    setFocusPolicy(Qt::StrongFocus);

    drag_cam_ = false;

    gui_update_timer_ = new QTimer(this);
    connect(gui_update_timer_, &QTimer::timeout,
            this, &View::UpdateGuiPositions);
}

View::~View()
{
}

void View::SetSceneManager(SceneManager* scene_mgr)
{
    scene_mgr_ = scene_mgr;
}

void View::ShowWidget(int w, int h)
{
    setSceneRect(0, 0, w, h);
    setFixedSize(w, h);

    cam_rect_[0] = w;
    cam_rect_[1] = h;

    cam_pos_max_[0] = scene_mgr_->GetPathGrid()->Width() - w;
    cam_pos_max_[1] = scene_mgr_->GetPathGrid()->Height() - h;

    showNormal();

    //    gui_update_timer_->start(0);
}

QPoint View::GetCenterCamPos() const
{
    double x = sceneRect().topLeft().x() + sceneRect().width() / 2;
    double y = sceneRect().topLeft().y() + sceneRect().height() / 2;

    return QPoint(x, y);
}

void View::SetCenterCamPos(QPointF position)
{

    double new_x = position.x() - cam_rect_[0] / 2;
    double new_y = position.y() - cam_rect_[1] / 2;

    static const int offset = 50;

    new_x = new_x < -offset ? -offset : new_x;
    new_x = new_x > cam_pos_max_[0] + offset ? cam_pos_max_[0] + offset : new_x;
    new_y = new_y < -offset ? -offset : new_y;
    new_y = new_y > cam_pos_max_[1] + offset ? cam_pos_max_[1] + offset : new_y;

    QPointF top_left(new_x, new_y);

    this->setSceneRect(top_left.x(), top_left.y(), cam_rect_[0], cam_rect_[1]);

    UpdateGuiPositions();
    this->scene()->update();
    this->update();
}

void View::mousePressEvent(QMouseEvent* event)
{
    QGraphicsView::mousePressEvent(event); // 执行正常的QGraphicsView事件处理
    if (event->isAccepted()) { // 事件已处理,结束
        return;
    }

    // 左键按下
    auto mouse_buttons = event->buttons();
    if (mouse_buttons & Qt::LeftButton) { // 不管按哪里，移动相机
        drag_cam_ = true;
        press_pos_ = event->pos();
        cam_center_pos_ = GetCenterCamPos();
    }
}

void View::mouseMoveEvent(QMouseEvent* event)
{
    QGraphicsView::mouseMoveEvent(event);

    if (drag_cam_) {
        const QPoint new_pos = cam_center_pos_ + press_pos_ - event->pos();
        SetCenterCamPos(new_pos);
    }
}

void View::mouseReleaseEvent(QMouseEvent* event)
{
    drag_cam_ = false;

    // 执行正常的QGraphicsView事件处理
    //    QGraphicsView::mouseReleaseEvent(event);
    //    if (event->isAccepted()) { // 事件已处理,结束
    //        return;
    //    }

    // 左键松开
    auto mouse_buttons = event->button();
    if (mouse_buttons == Qt::LeftButton
        && (press_pos_ - event->pos()).manhattanLength() < 10) {
        scene_mgr_->SgnMouseRelease();
    }
}

void View::keyPressEvent(QKeyEvent* event)
{
    static int angle = 0;
    static double scale = 1.0;

    switch (event->key()) {
    case Qt::Key_Left: {
        angle -= 15;

        QTransform matrix;
        matrix.scale(scale, scale);
        matrix.rotate(angle);
        setTransform(matrix);
        break;
    }
    case Qt::Key_Right: {
        angle += 15;

        QTransform matrix;
        matrix.scale(scale, scale);
        matrix.rotate(angle);
        setTransform(matrix);
        break;
    }
    case Qt::Key_Up: {

        scale *= 1.1;

        QTransform matrix;
        matrix.scale(scale, scale);
        matrix.rotate(angle);
        setTransform(matrix);
        break;
    }
    case Qt::Key_Down: {
        scale *= 0.9;

        QTransform matrix;
        matrix.scale(scale, scale);
        matrix.rotate(angle);
        setTransform(matrix);

        break;
    }
    default:
        break;
    }
}

void View::wheelEvent(QWheelEvent* event)
{
    Q_UNUSED(event)
}

void View::UpdateGuiPositions()
{
    scene_mgr_->GetGuiLayer()->setPos(mapToScene(QPoint(0, 0)));
}
