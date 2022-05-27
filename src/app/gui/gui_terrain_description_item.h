#ifndef GUITERRAINDESCRIPTIONITEM_H
#define GUITERRAINDESCRIPTIONITEM_H

#include "gui.h"
#include "scene/layout_terrain.h"

class TerrainDescriptionItem : public Gui, public QGraphicsItem
{
public:
    TerrainDescriptionItem(QGraphicsItem* parent = nullptr);

    void UpdataInfo(const QString& title, const QString& content);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override;

    void SetVisable(const bool& show) override;
    QGraphicsItem* GetGraphicsItem() override;

private:
    QRectF rect_;

    QString title_;
    QString content_;

    bool show_;
};

#endif // GUITERRAINDESCRIPTIONITEM_H
