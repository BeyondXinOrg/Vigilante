#ifndef GUITERRAINDESCRIPTION_H
#define GUITERRAINDESCRIPTION_H

#include "gui.h"
#include "scene/layout_terrain.h"

class TerrainDescriptionItem : public QGraphicsItem
{
public:
    TerrainDescriptionItem(QGraphicsItem* parent = nullptr);

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

class GuiTerrainDescription : public Gui
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
    GuiTerrainDescription();

    QGraphicsItem* GetGraphicsItem() override;
    void SetSceneManager(SceneManager* scene_mgr) override;

    void Describe(TerrainType& type);
    void ClearDescribe();

private:
    TerrainDescriptionItem* center_item_;
};

#endif // GUITERRAINDESCRIPTION_H
