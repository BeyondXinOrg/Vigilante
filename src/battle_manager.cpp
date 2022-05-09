﻿#include "battle_manager.h"

#include "data/cell_grid.h"
#include "gui/brief_property_panel.h"
#include "gui/gui.h"
#include "gui/gui_location_hero.h"
#include "gui/gui_skip_round.h"
#include "hero/hero.h"
#include "hero/hero_sheet.h"
#include "hero/hero_sprite.h"
#include "scene/layout_terrain.h"
#include "scene/path_grid.h"
#include "scene/path_map.h"
#include "scene/scene_manager.h"
#include "scene/tile_sheet.h"
#include "scene/view.h"

#include <QApplication>
#include <QThread>
#include <QTimer>

Hero* CreateHero(int x, int y, QString png)
{
    Hero* hero = new Hero();
    HeroSheet* hero_sheet = new HeroSheet(png, 16, 3, 64, 64);
    HeroSprite* hero_sprite = new HeroSprite();

    hero_sprite->AddAnimation("death_down", hero_sheet->TileAt(Cell(0, 0), Cell(1, 0)));

    hero_sprite->AddAnimation("attack_up", hero_sheet->TileAt(Cell(12, 1), Cell(15, 1)));
    hero_sprite->AddAnimation("attack_down", hero_sheet->TileAt(Cell(0, 1), Cell(3, 1)));
    hero_sprite->AddAnimation("attack_left", hero_sheet->TileAt(Cell(4, 1), Cell(7, 1)));
    hero_sprite->AddAnimation("attack_right", hero_sheet->TileAt(Cell(8, 1), Cell(11, 1)));

    hero_sprite->AddAnimation("move_up", hero_sheet->TileAt(Cell(12, 2), Cell(15, 2)));
    hero_sprite->AddAnimation("move_down", hero_sheet->TileAt(Cell(0, 2), Cell(3, 2)));
    hero_sprite->AddAnimation("move_left", hero_sheet->TileAt(Cell(4, 2), Cell(7, 2)));
    hero_sprite->AddAnimation("move_right", hero_sheet->TileAt(Cell(8, 2), Cell(11, 2)));

    hero_sprite->AddAnimation("stand_up", hero_sheet->TileAt(Cell(12, 2), Cell(13, 2)));
    hero_sprite->AddAnimation("stand_down", hero_sheet->TileAt(Cell(0, 2), Cell(1, 2)));
    hero_sprite->AddAnimation("stand_left", hero_sheet->TileAt(Cell(4, 2), Cell(5, 2)));
    hero_sprite->AddAnimation("stand_right", hero_sheet->TileAt(Cell(8, 2), Cell(9, 2)));

    hero->SetHeroSprite(hero_sprite);
    hero_sprite->PlayAnimation("stand_down");

    hero->SetCell(Cell(x, y));
    return hero;
}

BattleManager::BattleManager()
{
    cell_grid_ = new CellGrid(22, 15);
    scene_mgr_ = new SceneManager(cell_grid_, 128);

    ui_brief_property_ = new BriefPropertyPanel;
    scene_mgr_->AddGui(ui_brief_property_);

    ui_skip_round_ = new GUISkipRound;
    scene_mgr_->AddGui(ui_skip_round_);
    connect(ui_skip_round_, &GUISkipRound::SgnSkipRound,
            this, &BattleManager::SkipRound);

    ui_location_hero_ = new GUIlocationHero;
    scene_mgr_->AddGui(ui_location_hero_);
    ui_location_hero_->SetTargetHero();

    battle_timer_ = new QTimer(this);
    InitConnect();

    Hero* hero;

    hero = CreateHero(0, 0, u8"./sheet_舞女.png");
    if (scene_mgr_->AddHero(hero)) {
        heros_[hero] = KEnemy;
    }

    hero = CreateHero(0, 1, u8"./sheet_弓骑兵.png");
    if (scene_mgr_->AddHero(hero)) {
        heros_[hero] = KEnemy;
    }

    hero = CreateHero(9, 9, u8"./sheet_关羽骑马.png");
    if (scene_mgr_->AddHero(hero)) {
        heros_[hero] = KPlayer;
    }

    hero = CreateHero(9, 8, u8"./sheet_张飞骑马.png");
    if (scene_mgr_->AddHero(hero)) {
        heros_[hero] = KPlayer;
    }
}

void BattleManager::Launch()
{
    scene_mgr_->Launch();
    battle_timer_->start(20);
}

void BattleManager::InitConnect()
{
    connect(battle_timer_, &QTimer::timeout,
            this, &BattleManager::BattleTimeAdvance);

    connect(scene_mgr_, &SceneManager::SgnMouseRelease,
            this, &BattleManager::OnSceneCellSelect);
}

// 时间推进
void BattleManager::BattleTimeAdvance()
{
    auto i = heros_.begin();
    while (i != heros_.end()) {
        auto hero = i.key();

        int action_progress = hero->GetActionProgess();
        if (action_progress >= 100) { // 行动进度到达终点

            cur_round_hero_ = hero;
            cur_hero_ = hero;

            if (KPlayer == i.value()) {
                WaitOperationHero(cur_round_hero_);
            } else if (KEnemy == i.value()) {
                WaitOperationHero(cur_round_hero_);
            }

            return;
        }
        ++i;
    }

    i = heros_.begin();
    while (i != heros_.end()) {
        auto hero = i.key();
        // 英雄行动进度推进
        hero->ActionTimeAdvance();
        ++i;
    }
}

// 等待玩家操作英雄
void BattleManager::WaitOperationHero(Hero* hero)
{
    // 暂停时间
    battle_timer_->stop();
    ui_skip_round_->SetVisable(true);

    // 调整当前英雄状态
    hero->SetBattleState(KSelection_Destination);

    // 计算、显示当前操作英雄可移动路径
    scene_mgr_->MoveCamCenterToHero(cur_round_hero_);
    scene_mgr_->ShowHeroInstructions(cur_round_hero_);

    ui_location_hero_->SetTargetHero(cur_round_hero_);

    auto terrain_type = scene_mgr_->GetTerrainType(cur_round_hero_->GetCell());
    ui_brief_property_->Describe(terrain_type, cur_round_hero_);
}

// 等待AI操作英雄
void BattleManager::WaitAIOperationHero(Hero* hero)
{

    battle_timer_->stop();
    ui_skip_round_->SetVisable(true);
}

// 结束英雄操作，时间继续推进
void BattleManager::EndOperationHero(Hero* hero)
{
    // 调整复位英雄状态
    cur_round_hero_->SetBattleState(KEnergy_Storage);
    cur_round_hero_->ActionTimeReset(); // 行动进度清空
    // 清空英雄
    cur_round_hero_ = nullptr;
    // 时间
    ui_skip_round_->SetVisable(false);
    battle_timer_->start(20);
}

void BattleManager::SkipRound()
{
    EndOperationHero(cur_round_hero_);
}

// 场景中点击
void BattleManager::OnSceneCellSelect()
{
    /**
     *  本回合英雄
     *  当前英雄
     *  选择英雄
     */

    auto select_cell = scene_mgr_->GetCurMouseCell();
    auto select_hero = scene_mgr_->GetCurMouseHero();
    auto select_terrain_type = scene_mgr_->GetTerrainType(select_cell);

    bool show_moverange = true;

    if (cur_hero_ == cur_round_hero_) { // 当前英雄和本回合英雄相同
        auto battle_state = cur_round_hero_->GetBattleState();

        if (battle_state == KSelection_Destination) {
            if (cur_round_hero_->CanMoveToCell(select_cell)) {
                cur_round_hero_->SetTargetCell(select_cell);
                cur_round_hero_->SetBattleState(KConfirm_Destination);
            } else {
                cur_hero_ = select_hero;
            }
        } else if (battle_state == KConfirm_Destination) {
            if (select_cell == cur_round_hero_->GetTargetCell()) {
                cur_round_hero_->MoveToCell(select_cell);
                EndOperationHero(cur_round_hero_);
                show_moverange = false;
            } else if (cur_round_hero_->CanMoveToCell(select_cell)) {
                cur_round_hero_->SetTargetCell(select_cell);
                cur_round_hero_->SetBattleState(KSelection_Hero);
            } else {
                cur_hero_ = select_hero;
                cur_round_hero_->SetBattleState(KSelection_Destination);
            }
        }

    } else { // 当前英雄和本回合英雄不同
        cur_hero_ = select_hero;
    }

    if (cur_hero_ && show_moverange) {
        scene_mgr_->ShowHeroInstructions(cur_hero_);
    } else {
        scene_mgr_->ShowHeroInstructions(select_cell);
    }
    ui_brief_property_->Describe(select_terrain_type, select_hero);
}

//// 更新阵营边框
// void BattleManager::UpdataCampBlock()
//{
//     QList<Cell> player_cell;
//     QList<Cell> enemy_cell;

//    auto i = heros_.begin();
//    while (i != heros_.end()) {
//        if (KPlayer == i.value()) {
//            player_cell << i.key()->GetCell();
//        } else if (KEnemy == i.value()) {
//            enemy_cell << i.key()->GetCell();
//        }
//        ++i;
//    }
//}
