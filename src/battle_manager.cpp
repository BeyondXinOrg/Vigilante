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
    scene_mgr_->AddHero(hero);
    heros_[hero] = KEnemy;

    hero = GetHero(0, 1, 1);
    scene_mgr_->AddHero(hero);
    heros_[hero] = KEnemy;

    hero = GetHero(9, 9, 2);
    scene_mgr_->AddHero(hero);
    heros_[hero] = KPlayer;

    hero = GetHero(9, 8, 3);
    scene_mgr_->AddHero(hero);
    heros_[hero] = KPlayer;

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
        int action_progress = i.key()->TimeAdvance();
        if (action_progress >= 100) {
            //            if (Game_Player == i.value()) {
            //                WaitingOperationHero(i.key());
            //            } else if (Enemy == i.value()) {
            //                AIOperationHero(i.key());
            //            }
            battle_timer_->stop();
        }
        ++i;
    }
}
