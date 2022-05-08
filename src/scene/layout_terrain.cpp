#include "layout_terrain.h"

#include "data/cell_grid.h"
#include "hero/hero.h"
#include "scene/path_grid.h"
#include "scene/scene_manager.h"
#include "scene/tile_sheet.h"

#include <QPainter>
#include <QRandomGenerator>
#include <QRect>

LayoutTerrain::LayoutTerrain(QGraphicsItem* parent)
  : QGraphicsItem(parent)
{
    scene_mgr_ = nullptr;
    tile_sheet_ = nullptr;
}

QRectF LayoutTerrain::boundingRect() const
{
    return rect_;
}

void LayoutTerrain::paint(
  QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget)
{
    Q_UNUSED(item)
    Q_UNUSED(widget)

    painter->setPen(QPen(Qt::white, 2));
    painter->drawPixmap(0, 0, bg_pix_);
}

void LayoutTerrain::UpdataTerrainBg()
{
    if (!scene_mgr_ || !tile_sheet_) {
        return;
    }
    bg_pix_ = QPixmap(rect_.width(), rect_.height());
    bg_pix_.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&bg_pix_);

    const int cell_size = scene_mgr_->GetPathGrid()->CellSize();

    foreach (auto type, types_cell_.keys()) {

        auto tile_pix = tile_sheet_->TileAt(type);
        tile_pix = tile_pix.scaled(32, 32);

        foreach (auto cell, types_cell_.value(type)) {
            const QRect rect(cell.x * cell_size,
                             cell.y * cell_size,
                             cell_size,
                             cell_size);
            painter.drawPixmap(rect, tile_pix);
        }
    }

    painter.end();
}

void LayoutTerrain::Resize(int width, int heigh)
{
    rect_ = QRectF(0, 0, width, heigh);
    UpdataTerrainBg();
    update();
}

void LayoutTerrain::SetSceneManager(SceneManager* data)
{
    scene_mgr_ = data;

    cells_type_.reserve(
      scene_mgr_->GetCellGrid()->Cols() * scene_mgr_->GetCellGrid()->Rows() + 5);
    types_cell_.reserve(10);

    GenerateRandomTerrain();
    RefreshTypesCell();
}

void LayoutTerrain::SetTileSheetData(TileSheet* data)
{
    tile_sheet_ = data;
}

QList<Cell> LayoutTerrain::GetWallTerrainCell() const
{
    QList<Cell> cell;
    cell << types_cell_.value(KWall_Cell);
    return cell;
}

TerrainType LayoutTerrain::GetTerrainType(const Cell& cell)
{
    return cells_type_.value(cell);
}

RandomForest::RandomForest()
{
    QList<Cell> tree_type;
    tree_type << Cell(1, 0) << Cell(2, 0) << Cell(1, 1);
    tree_types_ << tree_type;
    tree_type.clear();

    tree_type << Cell(1, 0) << Cell(2, 0) << Cell(0, 1) << Cell(1, 1);
    tree_types_ << tree_type;
    tree_type.clear();

    tree_type << Cell(0, 1) << Cell(0, 2) << Cell(0, 3) << Cell(0, 4)
              << Cell(1, 1);
    tree_types_ << tree_type;
    tree_type.clear();

    tree_type << Cell(-1, 1) << Cell(0, 1) << Cell(1, 1) << Cell(0, 2);
    tree_types_ << tree_type;
    tree_type.clear();

    tree_type << Cell(-1, 1) << Cell(0, 1) << Cell(1, 1) << Cell(2, 1)
              << Cell(1, 0) << Cell(1, 2);
    tree_types_ << tree_type;
    tree_type.clear();

    tree_type << Cell(-1, 1) << Cell(0, 1) << Cell(1, 1) << Cell(0, 2)
              << Cell(-1, 2) << Cell(1, 0) << Cell(2, 0);
    tree_types_ << tree_type;
    tree_type.clear();

    tree_type << Cell(-1, 1) << Cell(0, 1) << Cell(1, 1) << Cell(2, 1)
              << Cell(-1, 2) << Cell(0, 2) << Cell(1, 2) << Cell(2, 2)
              << Cell(0, 3) << Cell(1, 3) << Cell(1, 4) << Cell(1, 0);
    tree_types_ << tree_type;
}

QList<Cell> RandomForest::GetForest(int id) const
{
    if (id >= tree_types_.size()) {
        id = -1;
    }
    if (-1 != id) {
        return tree_types_.at(id);
    }
    return tree_types_.at(QRandomGenerator::global()->bounded(tree_types_.size()));
}

int RandomForest::RandomForestSize(int min, int max)
{
    return min + QRandomGenerator::global()->bounded(max - min);
}

// 生成随机地图
void LayoutTerrain::GenerateRandomTerrain()
{
    auto grid = scene_mgr_->GetCellGrid();
    // 初始化数据
    foreach (auto cell, grid->Cells()) {
        cells_type_[cell] = KNormal_Cell;
    }

    // 增加随机墙
    int wall_size = cells_type_.size() * 0.45;
    for (int i = 0; i < wall_size; i++) {
        Cell cell = grid->RandomCell();
        if (cells_type_.value(cell) == KWall_Cell) {
            i--;
        } else {
            cells_type_[cell] = KWall_Cell;
        }
    }

    // 整理随机地图的墙和路
    SmoothWallWayMap(4, 2);
    //    SmoothWallWayMap(4, 2);
    //    SmoothWallWayMap(3, 4);
    //    SmoothWallWayMap(3, 4);

    // 增加树
    int forest_size = random_forest_.RandomForestSize();
    for (int i = 0; i < forest_size; i++) {
        Cell cell = grid->RandomCell(1);
        if (cells_type_.value(cell) != KNormal_Cell) {
            i--;
            continue;
        }
        auto tree_type = random_forest_.GetForest();
        cells_type_[cell] = KTree_Cell;
        foreach (auto offset, random_forest_.GetForest()) {
            auto new_cell = cell + offset;
            if (grid->Contains(new_cell)) {
                cells_type_[cell] = KTree_Cell;
            }
        }
    }
    cells_type_[Cell(0, 0)] = KNormal_Cell;
    cells_type_[Cell(0, 1)] = KNormal_Cell;
    cells_type_[Cell(9, 9)] = KNormal_Cell;
    cells_type_[Cell(9, 8)] = KNormal_Cell;
}

// 整理随机地图的墙和路
void LayoutTerrain::SmoothWallWayMap(int wall_bound, int way_bound)
{
    auto grid = scene_mgr_->GetCellGrid();
    foreach (auto cell, grid->Cells()) {
        int src_data = cells_type_.value(cell);
        auto neighbors = grid->Cell8Neighbors(cell);
        int size = 0;
        foreach (auto neighbor, neighbors) {
            if (src_data == cells_type_.value(neighbor)) {
                size++;
            }
        }

        if (KWall_Cell == src_data && size < wall_bound) {
            cells_type_[cell] = KNormal_Cell;
        } else if (KNormal_Cell == src_data && size < way_bound) {
            cells_type_[cell] = KWall_Cell;
        }
    }
}

// 刷新TypesCell数据
void LayoutTerrain::RefreshTypesCell()
{
    auto grid = scene_mgr_->GetCellGrid();
    types_cell_.clear();
    foreach (auto cell, grid->Cells()) {
        types_cell_[cells_type_.value(cell)] << cell;
    }
}
