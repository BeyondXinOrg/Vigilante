#ifndef GUITERRAINDESCRIPTION_H
#define GUITERRAINDESCRIPTION_H

#include "gui.h"
#include "scene/layout_terrain.h"

class TerrainDescriptionItem;
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
