#include "path_map.h"

#include <QHash>

PathMap::PathMap(CellGrid* grid)
  : grid_(grid)
{
    foreach (auto cell, grid_->Cells()) {
        filled_[cell] = false;
    }
}

void PathMap::Fill()
{
    foreach (auto cell, grid_->Cells()) {
        filled_[cell] = true;
    }
}

void PathMap::Fill(const Cell& cell)
{
    filled_[cell] = true;
}

void PathMap::UnFill()
{
    foreach (auto cell, grid_->Cells()) {
        filled_[cell] = false;
    }
}

void PathMap::UnFill(const Cell& cell)
{
    filled_[cell] = false;
}

bool PathMap::Filled(const Cell& cell) const
{
    return filled_[cell];
}

// 部分网格构成的树
// from 部分网格的中点
// power 部分网格的半径
Graph PathMap::PartGridToGraph(const Cell& from, const int& power) const
{
    const int col = grid_->Cols();
    const int row = grid_->Rows();

    int tl_x = from.x - power;
    int tl_y = from.y - power;
    int br_x = from.x + power;
    int br_y = from.y + power;

    tl_x = tl_x > 0 ? tl_x : 0;
    tl_x = tl_x < col - 1 ? tl_x : col - 1;
    tl_y = tl_y > 0 ? tl_y : 0;
    tl_y = tl_y < row - 1 ? tl_y : row - 1;
    br_x = br_x > 0 ? br_x : 0;
    br_x = br_x < col - 1 ? br_x : col - 1;
    br_y = br_y > 0 ? br_y : 0;
    br_y = br_y < row - 1 ? br_y : row - 1;

    Cell tl(tl_x, tl_y);
    Cell br(br_x, br_y);

    Graph g;
    // 增加节点
    g.AddCell(from);
    foreach (auto cell, grid_->Cells(tl, br)) {
        if (!Filled(cell)) {
            g.AddCell(cell);
        }
    }

    // 在未填充的节点之间添加所有边
    foreach (Cell node, g.Cells()) {
        // 获取节点的所有邻居
        QList<Cell> neighbors = grid_->Cell4Neighbors(node);
        foreach (Cell neighbor, neighbors) {
            if (!Filled(neighbor) && g.Contains(neighbor)) {
                g.AddEdge(node, neighbor, 1);
                g.AddEdge(neighbor, node, 1);
            }
        }
    }

    return g;
}

// 目标格子可以到达的位置
// from 目标格子
// power 行动力
QList<Cell> PathMap::CanReachPath(const Cell& from, const int& power) const
{
    return PartGridToGraph(from, power).GetPTCells(from, power);
}

// 返回移动路径
QList<Cell> PathMap::MovingPath(
  const Cell& from, const int& power, const Cell& to)
{
    auto cells = PartGridToGraph(from, power).GetPTCells(from, power);
    cells << from;

    Graph g;
    // 增加节点
    g.AddCell(from);
    foreach (auto cell, cells) {
        if (!Filled(cell)) {
            g.AddCell(cell);
        }
    }

    // 在未填充的节点之间添加所有边
    foreach (Cell node, g.Cells()) {
        // 获取节点的所有邻居
        QList<Cell> neighbors = grid_->Cell4Neighbors(node);
        foreach (Cell neighbor, neighbors) {
            if (!Filled(neighbor) && g.Contains(neighbor)) {
                g.AddEdge(node, neighbor, 1);
                g.AddEdge(neighbor, node, 1);
            }
        }
    }

    return g.ShortesPath(from, to);
}
