#include "layout_terrain.h"

#include "scene/path_grid.h"
#include "scene/terrain_map.h"
#include "scene/tile_sheet.h"

#include <QPainter>
#include <QRectF>

LayoutTerrain::LayoutTerrain(QGraphicsItem* parent)
  : QGraphicsItem(parent)
{
    path_grid_ = nullptr;
    tile_sheet_ = nullptr;
    terrain_map_ = nullptr;
}

QRectF LayoutTerrain::boundingRect() const
{
    return rect_;
}

void LayoutTerrain::paint(
  QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget)
{
    Q_UNUSED(item)
    Q_UNUSED(widget)

    painter->setPen(QPen(Qt::white, 2));
    painter->drawPixmap(0, 0, bg_pix_);
}

void LayoutTerrain::UpdataTerrainBg()
{
    if (!path_grid_ || !tile_sheet_ || !terrain_map_) {
        return;
    }
    bg_pix_ = QPixmap(rect_.width(), rect_.height());
    bg_pix_.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&bg_pix_);

    const int cell_size = path_grid_->CellSize();

    auto types = terrain_map_->GetAllTerrainType();

    foreach (auto type, types) {

        auto tile_pix = tile_sheet_->TileAt(type);
        tile_pix = tile_pix.scaled(32, 32);

        auto cells = terrain_map_->GetTerrainCell(type);
        foreach (auto cell, cells) {
            const QRect rect(cell.x * cell_size,
                             cell.y * cell_size,
                             cell_size,
                             cell_size);
            painter.drawPixmap(rect, tile_pix);
        }
    }

    painter.end();
}

void LayoutTerrain::Resize(int width, int heigh)
{
    rect_ = QRectF(0, 0, width, heigh);
    UpdataTerrainBg();
    update();
}

void LayoutTerrain::SetPathGrid(PathGrid* data)
{
    path_grid_ = data;
}

void LayoutTerrain::SetTileSheetData(TileSheet* data)
{
    tile_sheet_ = data;
}

void LayoutTerrain::SetTerrainMap(TerrainMap* data)
{
    terrain_map_ = data;
}
