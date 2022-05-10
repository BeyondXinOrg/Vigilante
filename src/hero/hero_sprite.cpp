#include "hero_sprite.h"

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
    text_item_ = new QGraphicsTextItem(this);
    text_item_->setPos(10, 5);
    QFont font;
    font.setPointSize(18);
    font.setBold(true);
    text_item_->setFont(font);
    text_item_->setDefaultTextColor(Qt::black);
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

// 临时打印属性
void HeroSprite::SetTempPreview(short blood, double progress)
{
    //    text_item_->setPlainText(
    //      QString("a:%1\n\nb:%2").arg(blood).arg(progress));
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
