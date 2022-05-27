#ifndef GUIHERODESCRIPTIONITEM_H
#define GUIHERODESCRIPTIONITEM_H

#include "gui.h"
#include "scene/layout_terrain.h"

class GuiButon;
class Hero;

class HeroDescriptionItem : public Gui, public QGraphicsItem
{
public:
    HeroDescriptionItem(QGraphicsItem* parent = nullptr);

    void UpdataInfo(const QString& title, const QString& content);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override;

    void SetVisable(const bool& show) override;
    QGraphicsItem* GetGraphicsItem() override;
    void SetSceneManager(SceneManager* scene_mgr) override;

private:
    QRectF rect_;

    QString title_;
    QString content_;

    bool show_;
};

#endif // GUIHERODESCRIPTIONITEM_H
