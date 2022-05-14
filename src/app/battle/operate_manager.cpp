#include "operate_manager.h"

#include "gui/gui_location_hero.h"
#include "gui/gui_skip_round.h"
#include "hero/hc_path_mover.h"
#include "scene/layout_colourful_cell.h"
#include "scene/scene_manager.h"

OperateManager::OperateManager(SceneManager* scene_mgr)
  : scene_mgr_(scene_mgr)
{
    ui_location_hero_ = new GUIlocationHero;
    scene_mgr_->AddGui(ui_location_hero_);
    ui_location_hero_->SetTargetHero();
    connect(ui_location_hero_, &GUIlocationHero::SgnClickedLocation,
            this, &OperateManager::SgnLocationOperateHero);

    ui_skip_round_ = new GUISkipRound;
    scene_mgr_->AddGui(ui_skip_round_);
    connect(ui_skip_round_, &GUISkipRound::SgnSkipRound,
            this, &OperateManager::SgnEndOperate);

    hc_path_mover_ = new HCPathMover;
    connect(hc_path_mover_, &HCPathMover::SgnSuccesfullyMoved,
            this, &OperateManager::OnHeroEndMoving);
}

void OperateManager::SetOperateHero(Hero* hero)
{
    cur_hero_ = hero;
    cur_hero_->SetOperate(true);
    can_operate_ = true;
    state_ = kOPE_None;
    ui_location_hero_->SetTargetHero(cur_hero_);
    scene_mgr_->MoveCamCenterToHero(cur_hero_);
    ui_skip_round_->SetVisable(true);
    ChangeShowHero(hero);
}

void OperateManager::ClickedPosition(const Cell& click_cell)
{

    if (!cur_hero_) {
        return;
    }

    auto click_hero = scene_mgr_->GetCurMouseHero(click_cell);

    if (!can_operate_) {
        if (click_hero == cur_hero_) {
            can_operate_ = true;
        }
    } else {
        switch (state_) {
        case kOPE_None: {
            if (cur_hero_->CanMoveToCell(click_cell)) { // 是否可以移动
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
                //                operate_hero_->MoveToCell(click_cell);
            } else if (cur_hero_->CanMoveToCell(click_cell)) { // 是否可以移动
                target_cell_ = click_cell;
                state_ = kREL_Select_Move;
            } else if (click_cell == cur_hero_->GetCell()) {
                state_ = kOPE_None;
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
          cur_hero_->GetMovingTrack(target_cell_));
    } else {
        scene_mgr_->GetLayoutColourfulCell()->HideMovingTrack();
    }

    if (state_ == kOPE_Moving) {
        ui_skip_round_->SetVisable(false);
        scene_mgr_->GetLayoutColourfulCell()->ClearSelect();
        hc_path_mover_->SetHeroControlled(cur_hero_);
        hc_path_mover_->MoveHero(cur_hero_->GetMovingTrack(target_cell_));
    }

    if (CanHandelClick() && can_operate_) {
        ChangeShowHero(cur_hero_);
    } else {
        ChangeShowHero(click_cell);
    }
}

bool OperateManager::CanOperate() const
{
    return can_operate_;
}

bool OperateManager::CanHandelClick() const
{
    if (state_ == kOPE_Moving || state_ == kOPE_Attack) {
        return false;
    }
    return true;
}

void OperateManager::ChangeShowHero(Hero* hero)
{
    scene_mgr_->GetLayoutColourfulCell()->SetSelectHero(cur_hero_);
}

void OperateManager::ChangeShowHero(Cell click_cell)
{
    auto click_hero = scene_mgr_->GetCurMouseHero(click_cell);
    if (click_hero) {
        scene_mgr_->GetLayoutColourfulCell()->SetSelectHero(click_hero);
    } else {
        scene_mgr_->GetLayoutColourfulCell()->SetSelectCell(click_cell);
    }
}

void OperateManager::ClearHero()
{
    scene_mgr_->GetLayoutColourfulCell()->ClearSelect();
}

void OperateManager::OnHeroEndMoving(HCPathMover* by_mover)
{
    if (by_mover == hc_path_mover_
        && state_ == kOPE_Moving) {
        ui_skip_round_->SetVisable(true);
        state_ = kOPE_None;
        ChangeShowHero(cur_hero_);
        //        emit SgnEndOperate();
        //        ClearHero();
    }
}
