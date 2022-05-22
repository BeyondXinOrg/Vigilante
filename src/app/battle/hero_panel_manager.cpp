#include "hero_panel_manager.h"

#include "gui/gui_hero_description.h"
#include "gui/gui_terrain_description.h"
#include "scene/scene_manager.h"

UIPanelManager::UIPanelManager(SceneManager* scene_mgr)
  : scene_mgr_(scene_mgr)
{
    ui_terrain_description_ = new GuiTerrainDescription();
    scene_mgr_->AddGui(ui_terrain_description_);

    ui_hero_description_ = new GuiHeroDescription();
    scene_mgr_->AddGui(ui_hero_description_);
}

void UIPanelManager::ChangeDescription(const Cell& cell)
{
    ChangeTerrainDescription(cell);
    ChangeHeroDescription(cell);
}

void UIPanelManager::ChangeTerrainDescription(const Cell& cell)
{
    auto terrain_type = scene_mgr_->GetTerrainType(cell);
    ui_terrain_description_->Describe(terrain_type);
}

void UIPanelManager::ChangeHeroDescription(const Cell& cell)
{
    auto hero = scene_mgr_->GetCellHero(cell);
    if (hero) {
        ui_hero_description_->Describe(hero);
    } else {
        ui_hero_description_->ClearDescribe();
    }
}

void UIPanelManager::ClearDecorate()
{
    ui_terrain_description_->ClearDescribe();
    ui_hero_description_->ClearDescribe();
}
