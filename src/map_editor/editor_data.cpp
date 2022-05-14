#include "editor_data.h"

#include "mediator.h"

#include <QBrush>
#include <QPainter>
#include <QPixmap>
#include <QVector2D>

EditorData::EditorData(Mediator& mediator, CellGrid* grid, int cell_size)
  : mediator_(mediator)
  , grid_(grid)
  , cell_size_(cell_size)
{
    foreach (auto cell, grid_->Cells()) {
        MapTileTypeItem* item = new MapTileTypeItem;
        tile_types_.insert(cell, item);
        item->setPos(CellToPoint(cell));
    }
}

// 所有像素块节点
// 所有像素块节点
Cell EditorData::PointToCell(const QPoint& pos) const
{
    int cellX = static_cast<int>(pos.x() / cell_size_);
    int cellY = static_cast<int>(pos.y() / cell_size_);
    return Cell(cellX, cellY);
}

Cell EditorData::PointToCell(const QPointF& pos) const
{
    int cellX = static_cast<int>(pos.x() / cell_size_);
    int cellY = static_cast<int>(pos.y() / cell_size_);
    return Cell(cellX, cellY);
}

QPointF EditorData::CellToPoint(const Cell& cell) const
{
    double pt_x = cell.x * cell_size_ + cell_size_ / 2;
    double pt_y = cell.y * cell_size_ + cell_size_ / 2;
    return QPointF(pt_x, pt_y);
}

QPointF EditorData::CellToTopLeftPoint(const Cell& cell) const
{
    double pt_x = cell.x * cell_size_;
    double pt_y = cell.y * cell_size_;
    return QPointF(pt_x, pt_y);
}

QRect EditorData::CellToRect(const Cell& cell) const
{
    return QRect(cell.x * cell_size_, cell.y * cell_size_, cell_size_,
                 cell_size_);
}

QRectF EditorData::CellToRectF(const Cell& cell) const
{
    return QRectF(cell.x * cell_size_, cell.y * cell_size_, cell_size_,
                  cell_size_);
}

void EditorData::AddTileTypesToScene()
{
    foreach (auto var, tile_types_) {
        mediator_.AddTileTypeItem(var);
    }
}
