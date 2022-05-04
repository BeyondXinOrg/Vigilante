#ifndef HEROSPRITE_H
#define HEROSPRITE_H

#include <QGraphicsItem>

class HeroSprite : public QObject,
                   public QGraphicsItem
{
    Q_OBJECT
public:
    HeroSprite(QGraphicsItem* parent = nullptr);
    void SetFixedFrame(const QPixmap& pix);

    QRectF boundingRect() const override;

    void SetSpritePos(QPointF pos_by_scene);

    void SetTempPreview(short blood, double progress);

protected:
    void paint(
      QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    void Initialize();

private:
    QGraphicsPixmapItem* pixmap_item_;
    QGraphicsTextItem* text_item_;
    //    QPixmap cur_animation_pix_;
};

#endif // HEROSPRITE_H
