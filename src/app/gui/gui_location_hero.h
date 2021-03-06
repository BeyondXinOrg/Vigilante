#ifndef GUILOCATIONHERO_H
#define GUILOCATIONHERO_H

#include "gui.h"

class Hero;
class GuiButon;

// 定位当前英雄
class GuiLocationHero : public Gui
{
    Q_OBJECT
public:
    GuiLocationHero();

    QGraphicsItem* GetGraphicsItem() override;
    void SetSceneManager(SceneManager* scene_mgr) override;

    void SetTargetHero(Hero* target_hero = nullptr);

Q_SIGNALS:
    void SgnClickedLocation();

private:
    void OnLoactionHero(GuiButon* panel, QPointF pos, int button);

private:
    GuiButon* location_btn_;

    Hero* target_hero_;
};

#endif // GUILOCATIONHERO_H
