#include "cell_grid.h"

#include <QRandomGenerator>

CellGrid::CellGrid(int num_cols, int num_rows)
  : num_cols_(num_cols)
  , num_rows_(num_rows)
{
}

// 所有像素块节点
QList<Cell> CellGrid::Cells() const
{
    return Cells(Cell(0, 0), Cell(num_cols_ - 1, num_rows_ - 1));
}

// 由左上角节点和右下角节点定义的矩形区域包围的节点
QList<Cell> CellGrid::Cells(const Cell& top_left,
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
bool CellGrid::Contains(const Cell& node) const
{
    return (node.x >= 0 && node.y >= 0 && node.x < num_cols_ && node.y < num_rows_);
}

// 获取8格邻居
QList<Cell> CellGrid::Cell8Neighbors(const Cell& of)
{
    QList<Cell> neighbors;

    if (of.y > 0) { // 上
        Cell cell(of.x, of.y - 1);
        neighbors << cell;
        if (of.x > 0) {
            Cell cell(of.x - 1, of.y - 1);
            neighbors << cell;
        }
        if (of.x < num_cols_ - 1) {
            Cell cell(of.x + 1, of.y - 1);
            neighbors << cell;
        }
    }

    if (of.y < num_rows_ - 1) { // 下
        Cell cell(of.x, of.y + 1);
        neighbors << cell;
        if (of.x > 0) {
            Cell cell(of.x - 1, of.y + 1);
            neighbors << cell;
        }
        if (of.x < num_cols_ - 1) {
            Cell cell(of.x + 1, of.y + 1);
            neighbors << cell;
        }
    }

    if (of.x > 0) { // 左
        Cell cell(of.x - 1, of.y);
        neighbors << cell;
    }

    if (of.x < num_cols_ - 1) { // 右
        Cell cell(of.x + 1, of.y);
        neighbors << cell;
    }

    return neighbors;
}

// 获取4格邻居
QList<Cell> CellGrid::Cell4Neighbors(const Cell& of)
{
    QList<Cell> neighbors;

    if (of.y > 0) { // 上
        Cell cell(of.x, of.y - 1);
        neighbors << cell;
    }

    if (of.y < num_rows_ - 1) { // 下
        Cell cell(of.x, of.y + 1);
        neighbors << cell;
    }

    if (of.x > 0) { // 左
        Cell cell(of.x - 1, of.y);
        neighbors << cell;
    }

    if (of.x < num_cols_ - 1) { // 右
        Cell cell(of.x + 1, of.y);
        neighbors << cell;
    }

    return neighbors;
}

// 获取随机格子
Cell CellGrid::RandomCell(int adjust) const
{
    return Cell(adjust + QRandomGenerator::global()->bounded(num_cols_ - adjust),
                adjust + QRandomGenerator::global()->bounded(num_rows_ - adjust));
}
