#include "gui_skip_round.h"

#include "gui/gui_buton.h"
#include "scene/scene_manager.h"

#include <QSize>

GUISkipRound::GUISkipRound()
  : location_btn_(new GuiButon())
{
    //    location_btn_->SetParentGui(this);
    target_hero_ = nullptr;

    connect(location_btn_, &GuiButon::SgnClicked,
            this, &GUISkipRound::OnLoactionHero);
}

QGraphicsItem* GUISkipRound::GetGraphicsItem()
{
    return location_btn_;
}

void GUISkipRound::SetSceneManager(SceneManager* scene_mgr)
{
    scene_mgr_ = scene_mgr;
    location_btn_->setVisible(false);
    location_btn_->setPos(QPointF(1920 - 50 - 50, 1080 - 300));
}

void GUISkipRound::OnLoactionHero(
  GuiButon* panel, QPointF pos, int button)
{
    Q_UNUSED(panel)
    Q_UNUSED(pos)
    Q_UNUSED(button)

    emit SgnSkipRound();
}
