#pragma execution_character_set("utf-8")

#include "gui_terrain_description_item.h"

#include <QDebug>
#include <QPainter>

TerrainDescriptionItem::TerrainDescriptionItem(QGraphicsItem* parent)
  : QGraphicsItem(parent)
{
    rect_.setRect(0, 0, 750, 150);

    title_ = " ";
    content_ = " ";
    show_ = false;
}

void TerrainDescriptionItem::UpdataInfo(const QString& title, const QString& content)
{
    title_ = title;
    content_ = content;
    update();
}

QRectF TerrainDescriptionItem::boundingRect() const
{
    return rect_;
}

void TerrainDescriptionItem::paint(
  QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget)
{
    Q_UNUSED(item)
    Q_UNUSED(widget)

    painter->save();

    if (show_) {
        painter->setPen(QColor(86, 74, 61));
        painter->setBrush(QColor(235, 209, 173, 125));
        painter->drawRect(rect_);
    }

    QFont font;
    font.setPointSize(25);
    painter->setPen(Qt::black);
    painter->setFont(font);
    painter->drawText(60, -15, title_);
    font.setPointSize(20);
    painter->setFont(font);
    painter->drawText(rect_.adjusted(10, 10, -10, -10), Qt::TextWordWrap | Qt::AlignLeft, content_);

    painter->restore();
}

void TerrainDescriptionItem::SetVisable(const bool& show)
{
    // 首次绘制 drawText 会造成卡顿，不使用自带的setVisable

    if (!show) {
        title_ = " ";
        content_ = " ";
    }
    show_ = show;
}

QGraphicsItem* TerrainDescriptionItem::GetGraphicsItem()
{
    return this;
}
