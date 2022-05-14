#ifndef BRIEFPROPERTYPANEL_H
#define BRIEFPROPERTYPANEL_H

#include "gui.h"

#include "scene/layout_terrain.h"

#include <QBrush>
#include <QHash>
#include <QPen>

class Hero;
class BriefPropertyItem;

class BriefPropertyPanel : public Gui
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
    BriefPropertyPanel();

    QGraphicsItem* GetGraphicsItem() override;
    void SetSceneManager(SceneManager* scene_mgr) override;

    void Describe(TerrainType& type, Hero* hero = nullptr);
    void ClearDescribe();

private:
    BriefPropertyItem* center_item_;
};

#endif // BRIEFPROPERTYPANEL_H
