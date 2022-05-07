#include "scene_manager.h"

#include "data/cell_grid.h"
#include "gui/gui.h"
#include "scene/layout_terrain.h"
#include "scene/path_grid.h"
#include "scene/path_map.h"
#include "scene/terrain_map.h"
#include "scene/tile_sheet.h"
#include "scene/view.h"

SceneManager::SceneManager(
  CellGrid* cell_grid, int cell_size, QObject* parint)
  : QObject(parint)
  , view_(new View())
  , scene_(new QGraphicsScene(this))

  , cell_grid_(cell_grid)
  , path_grid_(new PathGrid(cell_grid_, cell_size))
  , path_map_(new PathMap(cell_grid_))
  , terrain_map_(new TerrainMap(cell_grid_))

  , lay_terrain_(new LayoutTerrain())
  , lay_heros_(new QGraphicsRectItem())
{
    tile_sheet_ = new TileSheet("./2.png", 1, 5, 22, 22);
    tile_sheet_->SetTileCell(Cell(0, 0), KTree_Cell);
    tile_sheet_->SetTileCell(Cell(1, 0), KWall_Cell);
    tile_sheet_->SetTileCell(Cell(3, 0), KNormal_Cell);

    lay_terrain_->SetPathGrid(path_grid_);
    lay_terrain_->SetTileSheetData(tile_sheet_);
    lay_terrain_->SetTerrainMap(terrain_map_);
    lay_terrain_->Resize(path_grid_->Width(), path_grid_->Height());

    scene_->addItem(lay_terrain_);
    scene_->addItem(lay_heros_);

    QBrush bb;
    bb.setStyle(Qt::SolidPattern);
    bb.setColor(Qt::black);
    scene_->setBackgroundBrush(bb);

    view_->setScene(scene_);

    UpdataPathMap();
}

void SceneManager::Launch()
{
    view_->ShowWidget(path_grid_, 1920, 1080);
}

bool SceneManager::AddHero(Hero* hero)
{
    // 如果实体已在地图中，请不要执行任何操作
    if (heros_.contains(hero)) {
        return false;
    }

    // 人物目标路径有其他物品
    if (path_map_->Filled(hero->GetCell())) {
        return false;
    }

    hero->SetBattle(this);

    heros_ << hero;

    UpdataPathMap();

    return true;
}

void SceneManager::RemoveHero(Hero* hero)
{
    heros_.remove(hero);
}

QGraphicsRectItem* SceneManager::GetHerosLayer() const
{
    return lay_heros_;
}

QGraphicsRectItem* SceneManager::GetGuiLayer() const
{
    return lay_heros_;
}

PathGrid* SceneManager::GetPathGrid()
{
    return path_grid_;
}

PathMap* SceneManager::GetPathMap()
{
    return path_map_;
}

// 重新计算地图的路径地图
void SceneManager::UpdataPathMap()
{
    path_map_->UnFill();
    auto cells = terrain_map_->GetWallTerrainCell();
    foreach (auto cell, cells) {
        path_map_->Fill(cell);
    }
    foreach (auto hero, heros_) {
        path_map_->Fill(hero->GetCell());
    }
}

// 返回当前鼠标位置
Cell SceneManager::GetCurMouseCell() const
{
    QPointF mouse_pos = view_->mapToScene(view_->mapFromGlobal(view_->cursor().pos()));
    return path_grid_->PointToCell(mouse_pos);
}

void SceneManager::AddGui(Gui* gui)
{
    view_->AddGui(gui);
    gui->SetSceneManager(this);
}

QSize SceneManager::GetViewSize() const
{
    return view_->size();
}
