#include "path_grid.h"

#include <QRandomGenerator>
#include <QRect>

PathGrid::PathGrid(int num_cols, int num_rows, int cell_size)
  : num_cols_(num_cols)
  , num_rows_(num_rows)
  , cell_size_(cell_size)
{
    tiles_node_.reserve(num_cols_ * num_rows_ + 5);
    nodes_tile_.reserve(num_cols_ * num_rows_ + 5);
    nodes_.reserve(num_rows_);

    for (int i = 0; i < num_rows_; i++) {
        QList<Cell> col_of_nodes;
        for (int j = 0; j < num_cols; j++) {
            col_of_nodes << Cell(i, j);
        }
        nodes_ << col_of_nodes;
    }

    nodes_tile_ = GenerateRandomData();
    foreach (auto cell, Cells()) {
        tiles_node_[nodes_tile_.value(cell)] << cell;
    }
}

// 所有像素块节点
QList<Cell> PathGrid::Cells() const
{
    return Cells(Cell(0, 0), Cell(num_cols_, num_rows_));
}

// 由左上角节点和右下角节点定义的矩形区域包围的节点
QList<Cell> PathGrid::Cells(const Cell& top_left,
                            const Cell& bottom_right) const
{
    QList<Cell> cells;
    for (int x = top_left.x, max_x = bottom_right.x; x <= max_x; x++) {
        for (int y = top_left.y, max_y = bottom_right.y; y <= max_y; y++) {
            if (Contains(Cell(x, y))) {
                cells << Cell(x, y);
            }
        }
    }
    return cells;
}

// 像素快是否再图内
bool PathGrid::Contains(const Cell& node) const
{
    return (node.x >= 0 && node.y >= 0 && node.x < num_cols_ && node.y < num_rows_);
}

QList<TileType> PathGrid::GetAllTileType() const
{
    return tiles_node_.keys();
}

QVector<QRect> PathGrid::GetTileTypeRects(const TileType& type) const
{
    QVector<QRect> rects;

    foreach (auto var, tiles_node_.value(type)) {
        rects << QRect(var.x * cell_size_,
                       var.y * cell_size_,
                       cell_size_,
                       cell_size_);
    }

    return rects;
}

QList<Cell> PathGrid::CellNeighbors(const Cell& of, int col, int row)
{
    QList<Cell> neighbors;

    if (of.y > 0) { // 上
        Cell cell(of.x, of.y - 1);
        neighbors << cell;
        if (of.x > 0) {
            Cell cell(of.x - 1, of.y - 1);
            neighbors << cell;
        }
        if (of.x < col - 1) {
            Cell cell(of.x + 1, of.y - 1);
            neighbors << cell;
        }
    }

    if (of.y < row - 1) { // 下
        Cell cell(of.x, of.y + 1);
        neighbors << cell;
        if (of.x > 0) {
            Cell cell(of.x - 1, of.y + 1);
            neighbors << cell;
        }
        if (of.x < col - 1) {
            Cell cell(of.x + 1, of.y + 1);
            neighbors << cell;
        }
    }

    if (of.x > 0) { // 左
        Cell cell(of.x - 1, of.y);
        neighbors << cell;
    }

    if (of.x < col - 1) { // 右
        Cell cell(of.x + 1, of.y);
        neighbors << cell;
    }

    return neighbors;
}

void PathGrid::SmoothRefreshMap(
  QHash<Cell, TileType>& data, int wall_bound, int way_bound)
{
    const int row = num_rows_;
    const int col = num_cols_;

    foreach (auto cell, Cells()) {
        int src_data = data.value(cell);
        auto neighbors = CellNeighbors(cell, col, row);
        int size = 0;
        foreach (auto neighbor, neighbors) {
            if (src_data == data.value(neighbor)) {
                size++;
            }
        }

        if (KRockTIle == src_data && size < wall_bound) {
            data[cell] = KNormalTile;
        } else if (KNormalTile == src_data && size < way_bound) {
            data[cell] = KRockTIle;
        }
    }
}

QHash<Cell, TileType> PathGrid::GenerateRandomData()
{
    QHash<Cell, TileType> random_data;
    GenerateTreeType();

    const int row = num_rows_;
    const int col = num_cols_;

    // 初始化数据
    random_data.reserve(row * col);
    foreach (auto cell, Cells()) {
        random_data[cell] = KNormalTile;
    }

    // 增加随机墙
    int wall_size = random_data.size() * 0.55;
    for (int i = 0; i < wall_size; i++) {
        Cell cell(QRandomGenerator::global()->bounded(col), QRandomGenerator::global()->bounded(row));
        if (random_data.value(cell) == KRockTIle) {
            i--;
        } else {
            random_data[cell] = KRockTIle;
        }
    }

    // 组合 wall 和 way
    SmoothRefreshMap(random_data, 4, 2);
    SmoothRefreshMap(random_data, 4, 2);
    SmoothRefreshMap(random_data, 3, 4);
    SmoothRefreshMap(random_data, 3, 4);

    // 增加树
    int decorate_size = 5 + QRandomGenerator::global()->bounded(10);
    for (int i = 0; i < decorate_size; i++) {
        Cell cell(1 + QRandomGenerator::global()->bounded(col - 1),
                  1 + QRandomGenerator::global()->bounded(row - 1));
        if (random_data.value(cell) != KNormalTile) {
            i--;
            continue;
        }
        int type = QRandomGenerator::global()->bounded(tree_types_.size());
        auto tree_type = tree_types_.at(type);
        random_data[cell] = KTreeTIle;
        foreach (auto offset, tree_type) {
            auto new_cell = cell + offset;
            if (Contains(new_cell)) {
                random_data[new_cell] = KTreeTIle;
            }
        }
    }

    // 替换普通way
    QList<TileType> normal_types;
    normal_types << KNormalTile << KNormalTile1 << KNormalTile2;
    int types_size = normal_types.size();

    foreach (auto cell, Cells()) {
        int type = random_data.value(cell);
        if (type == KNormalTile) {
            auto type = normal_types.at(QRandomGenerator::global()->bounded(types_size));
            random_data[cell] = type;
        }
    }

    return random_data;
}

void PathGrid::GenerateTreeType()
{
    if (0 != tree_types_.size()) {
        return;
    }

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
