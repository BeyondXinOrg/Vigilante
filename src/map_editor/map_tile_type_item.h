#ifndef MAPTILETYPEITEM_H
#define MAPTILETYPEITEM_H

#include <QGraphicsItem>

#include "cell.h"

class MapTileTypeItem : public QGraphicsItem
{
public:
    MapTileTypeItem();

    virtual QRectF boundingRect() const override;

    virtual void paint(
      QPainter* painter,
      const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;

    QString TileType() const;

    void SetPixmap(const QPixmap& pixmap);

private:
    QString type_;
    QSizeF size_;
    QPixmap pixmap_;
    bool active_;

    Cell cell_;
    int cell_size_;
};

#endif // MAPTILETYPEITEM_H
