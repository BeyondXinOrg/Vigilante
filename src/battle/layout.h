#ifndef LAYOUT_H
#define LAYOUT_H

#include <QGraphicsItem>

class PathGrid;

class Layout : public QGraphicsItem
{
public:
    Layout(QGraphicsItem* parent = nullptr);
    ~Layout() override;

    QRectF boundingRect() const override;

    virtual void Resize(int width, int heigh);
    virtual void SetData(PathGrid* data);

protected:
    QRectF rect_;
    PathGrid* data_;
};

#endif // LAYOUT_H
