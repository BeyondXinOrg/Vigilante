#include "hero_sheet.h"

HeroSheet::HeroSheet(const QString str, int x, int y, int w, int h)
{
    sheet_grid_ = new CellGrid(x, y);
    w_ = w;
    h_ = h;

    pixmap_.load(str);
}

QPixmap HeroSheet::TileAt(const Cell& cell) const
{
    QRect tile_region;
    tile_region.setX(cell.x * w_);
    tile_region.setY(cell.y * h_);
    tile_region.setWidth(w_);
    tile_region.setHeight(h_);

    return pixmap_.copy(tile_region).scaled(128, 128);
}

QList<QPixmap> HeroSheet::TileAt(const Cell& tl, const Cell& bd) const
{
    QList<QPixmap> tiles;

    auto cells = sheet_grid_->Cells(tl, bd);

    foreach (Cell cell, cells) {
        tiles << TileAt(cell);
    }

    return tiles;
}
