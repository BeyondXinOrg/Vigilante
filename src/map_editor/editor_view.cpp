#include "editor_view.h"

#include "mediator.h"

#include <QScrollBar>
#include <QWheelEvent>

EditorView::EditorView(Mediator* mediator, QWidget* parent)
  : QGraphicsView(parent)
  , current_scale_(1)
  , max_scale_(20000)
  , min_scale_(.01)
  , mediator_(mediator)
{
    // 禁用QGraphicsView的滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 布局策略
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setAlignment(Qt::AlignCenter);

    // 追踪鼠标
    setMouseTracking(true);
    setDragMode(NoDrag);

    setFocusPolicy(Qt::StrongFocus);
}

EditorView::~EditorView()
{
}

// 缩放视图
void EditorView::ScaleScene(const double& new_scale)
{
    if (new_scale != current_scale_) {
        QTransform transform;
        transform.scale(new_scale, new_scale);
        setTransform(transform);
        current_scale_ = new_scale;
    }
}

// 沿着鼠标缩放视图
void EditorView::ScaleSceneByPoint(const double& new_scale, const QPointF& point)
{
    if (new_scale == current_scale_) {
        return;
    }

    // 获取当前鼠标相对于scene的位置;
    QPointF scene_pos = this->mapToScene(point.toPoint());

    // 获取当前鼠标位置相当于view大小的横纵比例;
    QPointF cur_scale(point.x() / viewport()->width(), point.y() / viewport()->height());

    QTransform matrix;
    matrix.scale(new_scale, new_scale);
    setTransform(matrix);
    current_scale_ = new_scale;

    // 将scene坐标转换为放大缩小后的坐标;
    QPointF view_point = matrix.map(scene_pos);
    // 通过滚动条控制view放大缩小后的展示scene的位置;
    horizontalScrollBar()->setValue(int(view_point.x() - viewport()->width() * cur_scale.x()));
    verticalScrollBar()->setValue(int(view_point.y() - viewport()->height() * cur_scale.y()));
}

void EditorView::UpdateSceneRect()
{
    const QRectF newSceneRect(0, 0, 128 * 20, 128 * 18);
    setSceneRect(newSceneRect);
    //    scene()->setSceneRect(newSceneRect);
}

void EditorView::mousePressEvent(QMouseEvent* event)
{
    mediator_->MousePress(event);
}

void EditorView::mouseMoveEvent(QMouseEvent* event)
{
    mediator_->MouseMove(event);
}

void EditorView::mouseReleaseEvent(QMouseEvent* event)
{
    mediator_->MouseRelease(event);
}

void EditorView::wheelEvent(QWheelEvent* event)
{

    const int delta = event->angleDelta().y();
    double new_scale = current_scale_;
    if (delta < 0) {
        new_scale *= 0.9;
        new_scale = new_scale < min_scale_ ? min_scale_ : new_scale;
    } else if (delta > 0) {
        new_scale *= 1.1;
        new_scale = new_scale > max_scale_ ? max_scale_ : new_scale;
    }
    ScaleSceneByPoint(new_scale, event->position());
}

void EditorView::closeEvent(QCloseEvent* event)
{
    Q_UNUSED(event)
}

void EditorView::leaveEvent(QEvent* event)
{
    Q_UNUSED(event)
}

void EditorView::keyPressEvent(QKeyEvent* event)
{
    Q_UNUSED(event)
}

void EditorView::enterEvent(QEvent* event)
{
    Q_UNUSED(event)
}
