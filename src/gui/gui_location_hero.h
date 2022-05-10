#ifndef GUILOCATIONHERO_H
#define GUILOCATIONHERO_H

#include "gui.h"

class Hero;
class GuiPanel;

class GUIlocationHero : public Gui
{
    Q_OBJECT
public:
    GUIlocationHero();

    QGraphicsItem* GetGraphicsItem() override;
    void SetSceneManager(SceneManager* scene_mgr) override;

    void SetTargetHero(Hero* target_hero = nullptr);

Q_SIGNALS:
    void SgnClickedLocation();

private:
    void OnLoactionHero(GuiPanel* panel, QPointF pos, int button);

private:
    GuiPanel* location_btn_;

    Hero* target_hero_;
};

#endif // GUILOCATIONHERO_H
