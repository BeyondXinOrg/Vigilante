#include "hero_panel_manager.h"

#include "gui/gui_terrain_description.h"
#include "scene/scene_manager.h"

UIPanelManager::UIPanelManager(SceneManager* scene_mgr)
  : scene_mgr_(scene_mgr)
{
    ui_terrain_description_ = new GuiTerrainDescription();
    scene_mgr_->AddGui(ui_terrain_description_);
}

void UIPanelManager::ClickedPosition(const Cell& cell)
{
    auto terrain_type = scene_mgr_->GetTerrainType(cell);
    ui_terrain_description_->Describe(terrain_type);
}

void UIPanelManager::ClearDecorate()
{
    ui_terrain_description_->ClearDescribe();
}
