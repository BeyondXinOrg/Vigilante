#include "map_tile_type_item.h"

#include <QPainter>
#include <QRectF>

MapTileTypeItem::MapTileTypeItem()
{
    size_ = QSize(128, 128);
    active_ = false;

    type_ = "normal_way";
}

QRectF MapTileTypeItem::boundingRect() const
{
    return QRectF(-size_.width() / 2, -size_.height() / 2,
                  size_.width(), size_.height());
}

void MapTileTypeItem::paint(
  QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->save();

    QPen pen;
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setBrush(Qt::NoBrush);
    pen.setColor(QColor(0, 0, 0));
    painter->setPen(pen);
    painter->drawRect(boundingRect());

    painter->drawPixmap(boundingRect().toRect(), pixmap_);

    if (active_) {
        painter->fillRect(boundingRect(), QBrush(QColor(0, 0, 0, 64)));
    }

    painter->restore();
}

QString MapTileTypeItem::TileType() const
{
    return type_;
}

void MapTileTypeItem::SetPixmap(const QPixmap& pixmap)
{
    pixmap_ = pixmap;
    update();
}
