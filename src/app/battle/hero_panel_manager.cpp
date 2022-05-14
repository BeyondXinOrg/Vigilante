#include "hero_panel_manager.h"

#include "scene/layout_colourful_cell.h"
#include "scene/scene_manager.h"

HeroPanelManager::HeroPanelManager(SceneManager* scene_mgr)
  : scene_mgr_(scene_mgr)
{
}

void HeroPanelManager::ChangeShowHero(Hero* hero)
{
    cur_hero_ = hero;
    scene_mgr_->GetLayoutColourfulCell()->SetSelectHero(cur_hero_);
}

void HeroPanelManager::ChangeShowHero(Cell click_cell)
{
    auto click_hero = scene_mgr_->GetCurMouseHero(click_cell);

    //    auto click_terrain = scene_mgr_->GetTerrainType(click_cell);

    if (click_hero) {
        cur_hero_ = click_hero;
        scene_mgr_->GetLayoutColourfulCell()->SetSelectHero(click_hero);
    } else {
        scene_mgr_->GetLayoutColourfulCell()->SetSelectCell(click_cell);
    }
}

void HeroPanelManager::ClearHero()
{
    scene_mgr_->GetLayoutColourfulCell()->ClearSelect();
}
