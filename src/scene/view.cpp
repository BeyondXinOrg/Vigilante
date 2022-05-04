#include "view.h"

#include <QDebug>
#include <QKeyEvent>

View::View(QWidget* parent)
  : QGraphicsView(parent)
{
    // 禁用QGraphicsView的滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 追踪鼠标
    setMouseTracking(true);

    setFocusPolicy(Qt::StrongFocus);
}

View::~View()
{
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

        qDebug() << scale;
        break;
    }
    case Qt::Key_Down: {
        scale *= 0.9;

        QTransform matrix;
        matrix.scale(scale, scale);
        matrix.rotate(angle);
        setTransform(matrix);

        qDebug() << scale;
        break;
    }
    default:
        break;
    }
}
