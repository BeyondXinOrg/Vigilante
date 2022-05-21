#ifndef GUIHERODESCRIPTION_H
#define GUIHERODESCRIPTION_H

#include "gui.h"
#include "scene/layout_terrain.h"

class Hero;

class HeroDescriptionItem : public QGraphicsItem
{
public:
    HeroDescriptionItem(QGraphicsItem* parent = nullptr);

    void UpdataInfo(const QString& title, const QString& content);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override;

    void SetVisible(const bool& show);

private:
    QRectF rect_;

    QString title_;
    QString content_;

    bool show_;
};

class GuiHeroDescription : public Gui
{
    Q_OBJECT
public:
    enum Type
    {
        kTerrainDescription,
        KHeroDescription,
        KNone,
    };

public:
    GuiHeroDescription();

    QGraphicsItem* GetGraphicsItem() override;
    void SetSceneManager(SceneManager* scene_mgr) override;

    void Describe(Hero* hero);
    void ClearDescribe();

private:
    HeroDescriptionItem* center_item_;
};

#endif // GUIHERODESCRIPTION_H
