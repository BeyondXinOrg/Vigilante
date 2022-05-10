#include "operate_manager.h"

#include "gui/gui_location_hero.h"
#include "gui/gui_skip_round.h"
#include "scene/layout_colourful_cell.h"
#include "scene/scene_manager.h"

OperateManager::OperateManager(SceneManager* scene_mgr)
  : scene_mgr_(scene_mgr)
{
    ui_location_hero_ = new GUIlocationHero;
    scene_mgr_->AddGui(ui_location_hero_);
    ui_location_hero_->SetTargetHero();

    ui_skip_round_ = new GUISkipRound;
    scene_mgr_->AddGui(ui_skip_round_);

    connect(ui_location_hero_, &GUIlocationHero::SgnClickedLocation,
            this, &OperateManager::SgnLocationOperateHero);

    connect(ui_skip_round_, &GUISkipRound::SgnSkipRound,
            this, &OperateManager::SgnEndOperate);
}

void OperateManager::SetOperateHero(Hero* hero)
{
    operate_hero_ = hero;
    can_operate_ = true;
    state_ = kOPE_None;
    ui_location_hero_->SetTargetHero(operate_hero_);
    scene_mgr_->MoveCamCenterToHero(operate_hero_);

    ui_skip_round_->SetVisable(!operate_hero_.isNull());
}

void OperateManager::ClickedPosition(const Cell& click_cell)
{

    if (!operate_hero_) {
        return;
    }

    auto click_hero = scene_mgr_->GetCurMouseHero(click_cell);

    if (!can_operate_) {
        if (click_hero == operate_hero_) {
            can_operate_ = true;
        }
    } else {
        switch (state_) {
        case kOPE_None: {
            if (operate_hero_->CanMoveToCell(click_cell)) { // 是否可以移动
                target_cell_ = click_cell;
                state_ = kREL_Select_Move;
            } else {
                can_operate_ = false;
            }
            break;
        }

        case kREL_Select_Move: {

            if (target_cell_ == click_cell) { // 确认移动
                state_ = kOPE_Moving;
                operate_hero_->MoveToCell(click_cell);
            } else if (operate_hero_->CanMoveToCell(click_cell)) { // 是否可以移动
                target_cell_ = click_cell;
                state_ = kREL_Select_Move;
            } else {
                can_operate_ = false;
                state_ = kOPE_None;
            }

            break;
        }

        default:
            break;
        }
    }

    if (state_ == kREL_Select_Move) {
        scene_mgr_->GetLayoutColourfulCell()->SetMovingTrack(
          operate_hero_->GetMovingTrack(target_cell_));
    } else {
        scene_mgr_->GetLayoutColourfulCell()->HideMovingTrack();
    }

    if (state_ == kOPE_Moving) {
        emit SgnEndOperate();
    }
}

bool OperateManager::CanOperate() const
{
    return can_operate_;
}
