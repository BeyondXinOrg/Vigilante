#ifndef GUISKIPROUND_H
#define GUISKIPROUND_H

#include "gui.h"

class Hero;
class GuiPanel;

class GUISkipRound : public Gui
{
    Q_OBJECT
public:
    GUISkipRound();

    QGraphicsItem* GetGraphicsItem() override;
    void SetSceneManager(SceneManager* scene_mgr) override;

    void SetVisable(bool show);

Q_SIGNALS:
    void SgnSkipRound();

private:
    void OnLoactionHero(GuiPanel* panel, QPointF pos, int button);

private:
    GuiPanel* location_btn_;

    Hero* target_hero_;
};

#endif // GUISKIPROUND_H
