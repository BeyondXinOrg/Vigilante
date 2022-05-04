#include "terrain_map.h"

#include <QRandomGenerator>
#include <QRect>

TerrainMap::TerrainMap(int num_cols, int num_rows)
  : grid_(new CellGrid(num_cols, num_rows))
{
    cells_type_.reserve(grid_->Cols() * grid_->Rows() + 5);
    types_cell_.reserve(10);

    GenerateRandomTerrain();
    RefreshTypesCell();
}

TerrainMap::TerrainMap(CellGrid* grid)
  : grid_(grid)
{
    cells_type_.reserve(grid_->Cols() * grid_->Rows() + 5);
    types_cell_.reserve(10);

    GenerateRandomTerrain();
    RefreshTypesCell();
}

QList<TerrainType> TerrainMap::GetAllTerrainType() const
{
    return types_cell_.keys();
}

QList<Cell> TerrainMap::GetTerrainCell(const TerrainType& type) const
{
    return types_cell_.value(type);
}

// 返回所有不能走的路，用来更新 path map
QList<Cell> TerrainMap::GetWallTerrainCell() const
{
    QList<Cell> cell;

    cell << types_cell_.value(KWall_Cell);

    return cell;
}

// 生成随机地图
void TerrainMap::GenerateRandomTerrain()
{

    // 初始化数据
    foreach (auto cell, grid_->Cells()) {
        cells_type_[cell] = KNormal_Cell;
    }

    // 增加随机墙
    int wall_size = cells_type_.size() * 0.45;
    for (int i = 0; i < wall_size; i++) {
        Cell cell = grid_->RandomCell();
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
        Cell cell = grid_->RandomCell(1);
        if (cells_type_.value(cell) != KNormal_Cell) {
            i--;
            continue;
        }
        auto tree_type = random_forest_.GetForest();
        cells_type_[cell] = KTree_Cell;
        foreach (auto offset, random_forest_.GetForest()) {
            auto new_cell = cell + offset;
            if (grid_->Contains(new_cell)) {
                cells_type_[cell] = KTree_Cell;
            }
        }
    }
}

// 整理随机地图的墙和路
void TerrainMap::SmoothWallWayMap(int wall_bound, int way_bound)
{
    foreach (auto cell, grid_->Cells()) {
        int src_data = cells_type_.value(cell);
        auto neighbors = grid_->Cell8Neighbors(cell);
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
void TerrainMap::RefreshTypesCell()
{
    types_cell_.clear();
    foreach (auto cell, grid_->Cells()) {
        types_cell_[cells_type_.value(cell)] << cell;
    }
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
