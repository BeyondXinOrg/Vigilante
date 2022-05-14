#ifndef CELLGRID_H
#define CELLGRID_H

#include "cell.h"

class CellGrid
{
public:
    CellGrid(int num_cols, int num_rows);

    int Cols() const; // 数据尺寸
    int Rows() const; // 数据尺寸

    QList<Cell> Cells() const;
    QList<Cell> Cells(const Cell& top_left, const Cell& bottom_right) const;
    bool Contains(const Cell& node) const;

    QList<Cell> Cell8Neighbors(const Cell& of);
    QList<Cell> Cell4Neighbors(const Cell& of);

    Cell RandomCell(int adjust = 1) const;

private:
    int num_cols_; // 列
    int num_rows_; // 行
};

inline int CellGrid::Cols() const
{
    return num_cols_;
}

inline int CellGrid::Rows() const
{
    return num_rows_;
}

#endif // CELLGRID_H
