#ifndef EDITORDATA_H
#define EDITORDATA_H

#include "cell.h"
#include "cell_grid.h"

#include "map_tile_type_item.h"
#include <QStack>

class Mediator;

class EditorData
{
public:
    EditorData(Mediator& mediator, CellGrid* grid, int cell_size);

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

    void AddTileTypesToScene();

private:
    Mediator& mediator_;

    CellGrid* grid_;
    int cell_size_;

    QHash<Cell, MapTileTypeItem*> tile_types_;
};

inline int EditorData::Width() const
{
    return grid_->Cols() * cell_size_;
}

inline int EditorData::Height() const
{
    return grid_->Rows() * cell_size_;
}

inline int EditorData::Cols() const
{
    return grid_->Cols();
}

inline int EditorData::Rows() const
{
    return grid_->Rows();
}

inline int EditorData::CellSize() const
{
    return cell_size_;
}

#endif // EDITORDATA_H
