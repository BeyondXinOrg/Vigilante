#include "hero_sprite.h"

HeroSprite::HeroSprite(QGraphicsItem* parent)
  : QGraphicsItem(parent)
{
    pixmap_item_ = new QGraphicsPixmapItem(this);
    Initialize();
}

void HeroSprite::SetFixedFrame(const QPixmap& pix)
{
    pixmap_item_->setPixmap(pix);
}

QRectF HeroSprite::boundingRect() const
{
    return pixmap_item_->boundingRect();
}

void HeroSprite::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
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
