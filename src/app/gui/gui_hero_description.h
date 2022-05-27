#ifndef GUIHERODESCRIPTION_H
#define GUIHERODESCRIPTION_H

#include "gui.h"
#include "scene/layout_terrain.h"

class GuiButon;
class Hero;
class HeroDescriptionItem;

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

Q_SIGNALS:
    void SgnClickedSkill(int id);

private:
    void OnClickSkill(GuiButon* panel, QPointF pos, int button);

private:
    HeroDescriptionItem* center_item_;

    QList<GuiButon*> location_btns_;
};

#endif // GUIHERODESCRIPTION_H
