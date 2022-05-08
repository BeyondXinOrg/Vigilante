#ifndef HEROSPRITE_H
#define HEROSPRITE_H

#include <QGraphicsItem>

class HeroSprite : public QObject,
                   public QGraphicsItem
{
    Q_OBJECT
public:
    HeroSprite(QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const override;

    void SetFixedFrame(const QPixmap& pix);

    void SetSpritePos(QPointF pos_by_scene);
    void SetTempPreview(short blood, double progress);

    void AddAnimation(const QString& name, const QList<QPixmap>& pixs);
    void PlayAnimation(const QString& name);

protected:
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;

private:
    void Initialize();

    void NextFrame();

private:
    QGraphicsPixmapItem* pixmap_item_;
    QGraphicsTextItem* text_item_;

    QHash<QString, QList<QPixmap>> animation_; // 动画
    QList<QPixmap> animation_pixs_;

    QTimer* animation_timer_;
    int animation_fps_;
    int animation_cur_frame_;
};

#endif // HEROSPRITE_H
