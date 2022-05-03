#ifndef PATHGRID_H
#define PATHGRID_H

#include "data/cell.h"

#include "battle/gridtype.h"

class PathGrid
{
public:
    PathGrid(int num_cols, int num_rows, int cell_size);

    int Width() const; // 数据尺寸
    int Height() const; // 数据尺寸
    int Cols() const; // 数据尺寸
    int Rows() const; // 数据尺寸
    int CellSize() const; // 像素尺寸

    QList<Cell> Cells() const;
    QList<Cell> Cells(const Cell& top_left, const Cell& bottom_right) const;
    bool Contains(const Cell& node) const;

    QList<TileType> GetAllTileType() const;
    QVector<QRect> GetTileTypeRects(const TileType& type) const;

private:
    QList<Cell> CellNeighbors(const Cell& of, int col, int rol);
    void SmoothRefreshMap(QHash<Cell, TileType> &data, int wall_bound = 4, int way_bound = 4);
    QHash<Cell, TileType> GenerateRandomData();
    void GenerateTreeType();

private:
    QList<QList<Cell>> nodes_;
    QHash<Cell, TileType> nodes_tile_;
    QHash<TileType, QList<Cell>> tiles_node_;

    int num_cols_; // 列
    int num_rows_; // 行
    int cell_size_;

    QList<QList<Cell>> tree_types_;
};

inline int PathGrid::Width() const
{
    return num_cols_ * cell_size_;
}

inline int PathGrid::Height() const
{
    return num_rows_ * cell_size_;
}

inline int PathGrid::Cols() const
{
    return num_cols_;
}

inline int PathGrid::Rows() const
{
    return num_rows_;
}

inline int PathGrid::CellSize() const
{
    return cell_size_;
}

#endif // PATHGRID_H
