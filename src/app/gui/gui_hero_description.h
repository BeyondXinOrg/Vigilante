#ifndef GUIHERODESCRIPTION_H
#define GUIHERODESCRIPTION_H

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

    QList<GuiButon*> location_btns_;
};

#endif // GUIHERODESCRIPTION_H
