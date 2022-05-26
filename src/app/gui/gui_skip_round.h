#ifndef GUISKIPROUND_H
#define GUISKIPROUND_H

#include "gui.h"

class Hero;
class GuiButon;

// 当前英雄跳过回合
class GUISkipRound : public Gui
{
    Q_OBJECT
public:
    GUISkipRound();

    QGraphicsItem* GetGraphicsItem() override;
    void SetSceneManager(SceneManager* scene_mgr) override;

Q_SIGNALS:
    void SgnSkipRound();

private:
    void OnLoactionHero(GuiButon* panel, QPointF pos, int button);

private:
    GuiButon* location_btn_;

    Hero* target_hero_;
};

#endif // GUISKIPROUND_H
