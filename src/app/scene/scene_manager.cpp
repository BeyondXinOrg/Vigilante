#include "scene_manager.h"

#include "data/cell_grid.h"
#include "gui/gui.h"
#include "scene/layout_terrain.h"
#include "scene/path_grid.h"
#include "scene/path_map.h"
#include "scene/view.h"
#include "terrain_decoration/terrain_decoration.h"

SceneManager::SceneManager(
  CellGrid* cell_grid, int cell_size, QObject* parint)
  : QObject(parint)
  , view_(new View())
  , scene_(new QGraphicsScene(this))

  , cell_grid_(cell_grid)
  , path_grid_(new PathGrid(cell_grid_, cell_size))
  , path_map_(new PathMap(cell_grid_))

  , lay_terrain_(new LayoutTerrain())
  , lay_terrain_decoration_(new QGraphicsRectItem())
  , lay_heros_(new QGraphicsRectItem())
  , lay_gui_(new QGraphicsRectItem())
{
    view_->SetSceneManager(this);

    QBrush bb;
    bb.setStyle(Qt::SolidPattern);
    bb.setColor(Qt::black);
    scene_->setBackgroundBrush(bb);

    view_->setScene(scene_);

    UpdataPathMap();
    InitConnect();

    scene_->addItem(lay_terrain_);
    scene_->addItem(lay_terrain_decoration_);
    scene_->addItem(lay_heros_);
    scene_->addItem(lay_gui_);
}

void SceneManager::SetSceneMap(const QString& pix_path)
{
    lay_terrain_->Resize(path_grid_->Width(), path_grid_->Height());
    lay_terrain_->SetSceneMap(pix_path);
}

void SceneManager::Launch()
{
    view_->ShowWidget(1920, 1080);
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
    return lay_gui_;
}

CellGrid* SceneManager::GetCellGrid() const
{
    return cell_grid_;
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
    //    auto cells = lay_terrain_->GetWallTerrainCell();
    //    foreach (auto cell, cells) {
    //        path_map_->Fill(cell);
    //    }
    foreach (auto hero, heros_) {
        path_map_->Fill(hero->GetCell());
    }
}

// 返回当前鼠标位置
Cell SceneManager::GetCurMouseCell() const
{
    QPointF mouse_pos = view_->mapToScene(
      view_->mapFromGlobal(view_->cursor().pos()));
    return path_grid_->PointToCell(mouse_pos);
}

Hero* SceneManager::GetCurMouseHero() const
{
    Cell cell = GetCurMouseCell();
    foreach (auto hero, heros_) {
        if (hero->GetCell() == cell) {
            return hero;
        }
    }
    return nullptr;
}

Hero* SceneManager::GetCellHero(const Cell& cell) const
{
    foreach (auto hero, heros_) {
        if (hero->GetCell() == cell) {
            return hero;
        }
    }
    return nullptr;
}

// 获取格子地形
TerrainType SceneManager::GetTerrainType(const Cell& cell) const
{
    return lay_terrain_->GetTerrainType(cell);
}

// 设置ui
void SceneManager::AddGui(Gui* gui)
{
    gui->GetGraphicsItem()->setParentItem(lay_gui_);
    gui->SetSceneManager(this);
}

// 设置地形装饰
void SceneManager::AddTerrainDecoration(TerrainDecoration* td)
{
    td->GetGraphicsItem()->setParentItem(lay_terrain_decoration_);
    td->SetSceneManager(this);
}

QSize SceneManager::GetViewSize() const
{
    return view_->size();
}

void SceneManager::MoveCamCenterToHero(Hero* hero)
{
    if (hero) {
        view_->SetCenterCamPos(path_grid_->CellToPoint(hero->GetCell()));
    }
}

void SceneManager::InitConnect()
{
}
