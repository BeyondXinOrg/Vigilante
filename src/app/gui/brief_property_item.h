#ifndef BRIEFPROPERTYITEM_H
#define BRIEFPROPERTYITEM_H

#include <QGraphicsItem>

class BriefPropertyItem : public QGraphicsItem
{
public:
    BriefPropertyItem(QGraphicsItem* parent = nullptr);

    void UpdataInfo(const QString& title, const QString& content);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override;

private:
    QRectF rect_;

    QString title_;
    QString content_;
};

#endif // BRIEFPROPERTYITEM_H
