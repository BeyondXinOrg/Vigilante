#include "path_grid.h"

#include <QPointF>
#include <QRectF>

PathGrid::PathGrid(CellGrid* grid, int cell_size)
  : grid_(grid)
  , cell_size_(cell_size)
{
}

// 所有像素块节点
Cell PathGrid::PointToCell(const QPoint& pos) const
{
    int cellX = static_cast<int>(pos.x() / cell_size_);
    int cellY = static_cast<int>(pos.y() / cell_size_);
    return Cell(cellX, cellY);
}

Cell PathGrid::PointToCell(const QPointF& pos) const
{
    int cellX = static_cast<int>(pos.x() / cell_size_);
    int cellY = static_cast<int>(pos.y() / cell_size_);
    return Cell(cellX, cellY);
}

QPointF PathGrid::CellToPoint(const Cell& cell) const
{
    double pt_x = cell.x * cell_size_ + cell_size_ / 2;
    double pt_y = cell.y * cell_size_ + cell_size_ / 2;
    return QPointF(pt_x, pt_y);
}

QPointF PathGrid::CellToTopLeftPoint(const Cell& cell) const
{
    double pt_x = cell.x * cell_size_;
    double pt_y = cell.y * cell_size_;
    return QPointF(pt_x, pt_y);
}

QRect PathGrid::CellToRect(const Cell& cell) const
{
    return QRect(cell.x * cell_size_, cell.y * cell_size_, cell_size_,
                 cell_size_);
}

QRectF PathGrid::CellToRectF(const Cell& cell) const
{
    return QRectF(cell.x * cell_size_, cell.y * cell_size_, cell_size_,
                  cell_size_);
}
