#include "battle_manager.h"

#include "data/cell_grid.h"
#include "gui/colourful_map_block.h"
#include "gui/gui.h"
#include "hero/hero.h"
#include "hero/hero_sprite.h"
#include "scene/layout_terrain.h"
#include "scene/path_grid.h"
#include "scene/path_map.h"
#include "scene/scene_manager.h"
#include "scene/terrain_map.h"
#include "scene/tile_sheet.h"
#include "scene/view.h"

#include <QApplication>
#include <QThread>
#include <QTimer>

Hero* GetHero(int x, int y, int sprite_id)
{
    Hero* hero = new Hero();
    HeroSprite* hero_sprite = new HeroSprite();
    hero_sprite->SetFixedFrame(
      QPixmap("./a.png").copy(sprite_id * 200, 0, 200, 200).scaled(80, 80));
    hero->SetHeroSprite(hero_sprite);
    hero->SetCell(Cell(x, y));
    return hero;
}

BattleManager::BattleManager()
{
    cell_grid_ = new CellGrid(10, 10);

    scene_mgr_ = new SceneManager(cell_grid_, 128);

    Hero* hero;

    hero = GetHero(0, 0, 0);
    if (scene_mgr_->AddHero(hero)) {
        heros_[hero] = KEnemy;
    }

    hero = GetHero(0, 1, 1);
    if (scene_mgr_->AddHero(hero)) {
        heros_[hero] = KEnemy;
    }

    hero = GetHero(9, 9, 2);
    if (scene_mgr_->AddHero(hero)) {
        heros_[hero] = KPlayer;
    }

    hero = GetHero(9, 8, 3);
    if (scene_mgr_->AddHero(hero)) {
        heros_[hero] = KPlayer;
    }

    colourful_map_block_ = new ColourfulMapBlock;
    scene_mgr_->AddGui(colourful_map_block_);

    UpdataCampBlock();

    battle_timer_ = new QTimer(this);
    connect(battle_timer_, &QTimer::timeout,
            this, &BattleManager::BattleTimeAdvance);
}

void BattleManager::Launch()
{
    scene_mgr_->Launch();
    battle_timer_->start(20);
}

// 更新阵营边框
void BattleManager::UpdataCampBlock()
{
    QList<Cell> player_cell;
    QList<Cell> enemy_cell;

    auto i = heros_.begin();
    while (i != heros_.end()) {
        if (KPlayer == i.value()) {
            player_cell << i.key()->GetCell();
        } else if (KEnemy == i.value()) {
            enemy_cell << i.key()->GetCell();
        }
        ++i;
    }
    colourful_map_block_->UpdataCampBlock(player_cell, enemy_cell);
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
            colourful_map_block_->ShowCurHeroBlock(cur_hero_->GetCell());

            if (KPlayer == i.value()) {
                WaitOperationHero(cur_hero_);
            } else if (KEnemy == i.value()) {
                WaitOperationHero(cur_hero_);
            }

            qDebug() << hero;
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
    auto cur_hero_move_range_ = hero->GetMovingRange();
    colourful_map_block_->ShowMovingRangeBlock(cur_hero_move_range_);

    QApplication::processEvents();
    QThread::msleep(500);
    EndOperationHero(hero);
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
    colourful_map_block_->ShowMovingRangeBlock();
    cur_hero_ = nullptr;
    // 时间
    battle_timer_->start();
}
