#include "layout_terrain.h"

#include <QPainter>

#include "battle/path_grid.h"
#include "battle/tile_sheet.h"

LayoutTerrain::LayoutTerrain(QGraphicsItem* parent)
  : Layout(parent)
{
}

void LayoutTerrain::paint(
  QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget)
{
    Q_UNUSED(item)
    Q_UNUSED(widget)

    painter->setPen(Qt::NoPen);

    auto types = data_->GetAllTileType();
    foreach (auto type, types) {
        auto tile_pix = tile_sheet_->TileAt(type);
        auto rects = data_->GetTileTypeRects(type);
        foreach (auto rect, rects) {
            painter->drawPixmap(rect, tile_pix);
        }
    }
}

void LayoutTerrain::SetTileSheetData(TileSheet* data)
{
    tile_sheet_ = data;
}
