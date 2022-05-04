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

Hero* GetHero(int x, int y, int sprite_id)
{
    Hero* hero = new Hero();
    HeroSprite* hero_sprite = new HeroSprite();
    hero_sprite->SetFixedFrame(
      QPixmap("./a.png").copy(sprite_id * 200, 0, 200, 200).scaled(128, 128));
    hero->SetHeroSprite(hero_sprite);
    hero->SetCell(Cell(x, y));
    return hero;
}

BattleManager::BattleManager()
{
    cell_grid_ = new CellGrid(10, 10);

    scene_mgr_ = new SceneManager(cell_grid_, 128);

    scene_mgr_->AddHero(GetHero(6, 6, 0));
    scene_mgr_->AddHero(GetHero(6, 7, 1));
    scene_mgr_->AddHero(GetHero(1, 1, 2));
    scene_mgr_->AddHero(GetHero(1, 3, 3));

    colourful_map_block_ = new ColourfulMapBlock;
    scene_mgr_->AddGui(colourful_map_block_);
}

void BattleManager::Launch()
{
    scene_mgr_->Launch();
}
