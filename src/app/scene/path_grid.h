#ifndef PATHGRID_H
#define PATHGRID_H

#include "data/cell_grid.h"

class PathGrid
{
public:
    PathGrid(CellGrid* grid, int cell_size);

    int Width() const; // 数据尺寸
    int Height() const; // 数据尺寸
    int Cols() const; // 数据尺寸
    int Rows() const; // 数据尺寸
    int CellSize() const; // 像素尺寸

    Cell PointToCell(const QPoint& pos) const;
    Cell PointToCell(const QPointF& pos) const;
    QPointF CellToPoint(const Cell& cell) const;
    QPointF CellToTopLeftPoint(const Cell& cell) const;
    QRect CellToRect(const Cell& cell) const;
    QRectF CellToRectF(const Cell& cell) const;

private:
    CellGrid* grid_;
    int cell_size_;
};

inline int PathGrid::Width() const
{
    return grid_->Cols() * cell_size_;
}

inline int PathGrid::Height() const
{
    return grid_->Rows() * cell_size_;
}

inline int PathGrid::Cols() const
{
    return grid_->Cols();
}

inline int PathGrid::Rows() const
{
    return grid_->Rows();
}

inline int PathGrid::CellSize() const
{
    return cell_size_;
}

#endif // PATHGRID_H
