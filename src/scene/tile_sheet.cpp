#include "tile_sheet.h"

#include <QRandomGenerator>

TileSheet::TileSheet(
  QString file_path, int num_xtiles, int num_ytiles,
  double tile_width, double tile_height)
  : pixmap_(QPixmap(file_path))
  , num_xtiles_(num_xtiles)
  , num_ytiles_(num_ytiles)
  , tile_width_(tile_width)
  , tile_height_(tile_height)
{
}

QPixmap TileSheet::TileAt(const TerrainType& type) const
{
    return tiles_.value(type);
}

void TileSheet::SetTileCell(const Cell& cell, const TerrainType& type)
{
    QRect region;
    region.setX(cell.x * tile_width_);
    region.setY(cell.y * tile_height_);
    region.setWidth(tile_width_);
    region.setHeight(tile_height_);

    tiles_[type] = pixmap_.copy(region);
}
