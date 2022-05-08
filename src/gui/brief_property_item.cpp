#include "brief_property_item.h"

#include <QDebug>
#include <QPainter>

BriefPropertyItem::BriefPropertyItem(QGraphicsItem* parent)
  : QGraphicsItem(parent)
{
    rect_.setRect(0, 0, 750, 150);

    title_ = "aaa";
    content_ = "aaa";
}

void BriefPropertyItem::UpdataInfo(const QString& title, const QString& content)
{
    title_ = title;
    content_ = content;
    update();
}

QRectF BriefPropertyItem::boundingRect() const
{
    return rect_;
}

void BriefPropertyItem::paint(
  QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget)
{
    Q_UNUSED(item)
    Q_UNUSED(widget)

    painter->save();

    painter->setPen(QColor(86, 74, 61));
    painter->setBrush(QColor(235, 209, 173, 125));
    painter->drawRect(rect_);

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
