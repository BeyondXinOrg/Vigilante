#include "gui_location_hero.h"

#include "gui/gui_panel.h"
#include "scene/scene_manager.h"

#include <QSize>

GUIlocationHero::GUIlocationHero()
  : location_btn_(new GuiPanel())
{
    //    location_btn_->SetParentGui(this);
    target_hero_ = nullptr;

    connect(location_btn_, &GuiPanel::SgnClicked,
            this, &GUIlocationHero::OnLoactionHero);
}

QGraphicsItem* GUIlocationHero::GetGraphicsItem()
{
    return location_btn_;
}

void GUIlocationHero::SetSceneManager(SceneManager* scene_mgr)
{
    scene_mgr_ = scene_mgr;
    location_btn_->setVisible(false);
    location_btn_->setPos(QPointF(50, 1080 - 300));
}

void GUIlocationHero::SetTargetHero(Hero* target_hero)
{
    target_hero_ = target_hero;
    if (target_hero_) {
        location_btn_->setVisible(true);
    }
}

void GUIlocationHero::OnLoactionHero(
  GuiPanel* panel, QPointF pos, int button)
{
    Q_UNUSED(panel)
    Q_UNUSED(pos)
    Q_UNUSED(button)

    emit SgnClickedLocation();

    //    scene_mgr_->ShowHeroInstructions(target_hero_);
    //    scene_mgr_->MoveCamCenterToHero(target_hero_);
}
