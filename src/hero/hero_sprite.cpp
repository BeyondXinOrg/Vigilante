#include "hero_sprite.h"

#include <QFont>
#include <QRectF>

HeroSprite::HeroSprite(QGraphicsItem* parent)
  : QGraphicsItem(parent)
{
    pixmap_item_ = new QGraphicsPixmapItem(this);
    pixmap_item_->setPos(24, 24);
    text_item_ = new QGraphicsTextItem(this);
    text_item_->setPos(10, 5);
    QFont font;
    font.setPointSize(18);
    font.setBold(true);
    text_item_->setFont(font);
    text_item_->setDefaultTextColor(Qt::black);
    Initialize();
}

void HeroSprite::SetFixedFrame(const QPixmap& pix)
{
    pixmap_item_->setPixmap(pix);
}

QRectF HeroSprite::boundingRect() const
{
    //    return pixmap_item_->boundingRect();
    QRectF rect(0, 0, 128, 128);
    return rect;
}

void HeroSprite::paint(
  QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void HeroSprite::Initialize()
{
}

// 放置位置 （世界坐标）
void HeroSprite::SetSpritePos(QPointF pos_by_scene)
{
    setPos(pos_by_scene - boundingRect().center());
}

void HeroSprite::SetTempPreview(short blood, double progress)
{
    text_item_->setPlainText(
      QString("a:%1\n\nb:%2").arg(blood).arg(progress));
}
