﻿#include "hero_sprite.h"

#include <QDebug>
#include <QFont>
#include <QRectF>
#include <QTimer>

/// 将秒转换为毫秒。
double SecondsToMs(double seconds)
{
    static const int MS_IN_S = 1000;
    double ms = seconds * MS_IN_S;
    return ms;
}

HeroSprite::HeroSprite(QGraphicsItem* parent)
  : QGraphicsItem(parent)
{
    pixmap_item_ = new QGraphicsPixmapItem(this);
    pixmap_item_->setPos(0, 0);
    pixmap_item_->setZValue(0);

    xu_li_item_ = new QGraphicsPixmapItem(this);
    xu_li_pix_ = QPixmap("./xu_li.png").scaled(128, 10);
    xu_li_item_->setPos(0, 10);
    xu_li_item_->setZValue(1);

    xue_liang_item_ = new QGraphicsPixmapItem(this);
    xue_liang_pix_ = QPixmap("./xue_cao.png").scaled(128, 10);
    xue_liang_item_->setPos(0, -3);
    xue_liang_item_->setZValue(1);

    UpdataState(0, 1);

    Initialize();
}

// 获取 item 边界
QRectF HeroSprite::boundingRect() const
{
    QRectF rect(0, 0, 128, 128);
    return rect;
}

// 放置位置 （世界坐标）
void HeroSprite::SetSpritePos(QPointF pos_by_scene)
{
    setPos(pos_by_scene - boundingRect().center());
}

// 增加动画
void HeroSprite::AddAnimation(const QString& name, const QList<QPixmap>& pixs)
{
    animation_[name] = pixs;
}

// 设置固定图片
void HeroSprite::SetFixedFrame(const QPixmap& pix)
{
    pixmap_item_->setPixmap(pix);
}

// 播放动画
void HeroSprite::PlayAnimation(const QString& name)
{
    cur_animation_ = name;
    animation_timer_->disconnect();

    animation_pixs_ = animation_[name];

    connect(animation_timer_, &QTimer::timeout, this, &HeroSprite::NextFrame);
    animation_cur_frame_ = 0;
    animation_timer_->start(SecondsToMs(1.0 / animation_fps_));
}

QString HeroSprite::CurAnimation() const
{
    return cur_animation_;
}

void HeroSprite::UpdataState(double xuli, double xue_liang)
{
    xu_li_item_->setPixmap(
      xu_li_pix_.scaled(xuli * 128, 10));

    xue_liang_item_->setPixmap(
      xue_liang_pix_.scaled(xue_liang * 128, 10));
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
    animation_timer_ = new QTimer(this);
    animation_fps_ = 8;
    animation_cur_frame_ = 0;
}

// 切换下一帧
void HeroSprite::NextFrame()
{
    pixmap_item_->setPixmap(animation_pixs_.at(animation_cur_frame_));
    animation_cur_frame_++;
    if (animation_cur_frame_ == animation_pixs_.size()) {
        animation_cur_frame_ = 0;
    }
}
