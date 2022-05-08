#include "battle_manager.h"

#include "data/cell_grid.h"
#include "gui/brief_property_panel.h"
#include "gui/gui.h"
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

Hero* CreateHero(int x, int y, int sprite_id)
{
    Hero* hero = new Hero();
    HeroSheet* hero_sheet = new HeroSheet("./b.png", 16, 3, 64, 64);
    HeroSprite* hero_sprite = new HeroSprite();

    hero_sprite->AddAnimation("death_up", hero_sheet->TileAt(Cell(12, 0), Cell(15, 0)));
    hero_sprite->AddAnimation("death_down", hero_sheet->TileAt(Cell(0, 0), Cell(3, 0)));
    hero_sprite->AddAnimation("death_left", hero_sheet->TileAt(Cell(4, 0), Cell(7, 0)));
    hero_sprite->AddAnimation("death_right", hero_sheet->TileAt(Cell(8, 0), Cell(11, 0)));

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

    battle_timer_ = new QTimer(this);
    InitConnect();

    Hero* hero;

    hero = CreateHero(0, 0, 0);
    if (scene_mgr_->AddHero(hero)) {
        heros_[hero] = KEnemy;
    }

    hero = CreateHero(0, 1, 1);
    if (scene_mgr_->AddHero(hero)) {
        heros_[hero] = KEnemy;
    }

    hero = CreateHero(9, 9, 2);
    if (scene_mgr_->AddHero(hero)) {
        heros_[hero] = KPlayer;
    }

    hero = CreateHero(9, 8, 3);
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

        // 英雄行动进度推进
        int action_progress = hero->ActionTimeAdvance();
        if (action_progress >= 100) { // 行动进度到达终点

            cur_hero_ = hero;
            cur_hero_->ActionTimeReset(); // 行动进度清空

            if (KPlayer == i.value()) {
                WaitOperationHero(cur_hero_);
            } else if (KEnemy == i.value()) {
                WaitOperationHero(cur_hero_);
            }
        }
        ++i;
    }
}

// 等待玩家操作英雄
void BattleManager::WaitOperationHero(Hero* hero)
{
    // 暂停时间
    battle_timer_->stop();
    // 调整当前英雄状态
    hero->SetBattleState(KSelectionDestination);

    // 计算、显示当前操作英雄可移动路径
    scene_mgr_->ShowHeroInstructions(cur_hero_);

    //    auto cur_hero_move_range_ = hero->GetMovingRange();

    //    QApplication::processEvents();
    //    QThread::msleep(500);
    //    EndOperationHero(hero);
}

// 等待AI操作英雄
void BattleManager::WaitAIOperationHero(Hero* hero)
{
    battle_timer_->stop();
}

// 结束英雄操作，时间继续推进
void BattleManager::EndOperationHero(Hero* hero)
{
    // 调整复位英雄状态
    hero->SetBattleState(KEnergyStorage);
    // 清空英雄可移动路径
    cur_hero_ = nullptr;
    // 时间
    battle_timer_->start();
}

// 场景中点击
void BattleManager::OnSceneCellSelect()
{
    //

    auto hero = scene_mgr_->GetCurMouseHero();
    scene_mgr_->ShowHeroInstructions(hero);
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
