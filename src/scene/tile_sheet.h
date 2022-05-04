#ifndef TILESHEET_H
#define TILESHEET_H

#include <QHash>
#include <QPixmap>

#include "scene/terrain_map.h"
#include "data/cell.h"

class TileSheet
{
public:
    TileSheet(QString file_path,
              int num_xtiles,
              int num_ytiles,
              double tile_width,
              double tile_height);

    QPixmap TileAt(const TerrainType& type) const;
    void SetTileCell(const Cell& cell, const TerrainType& type);

private:
    QPixmap pixmap_;
    QHash<TerrainType, QPixmap> tiles_;

    int num_xtiles_;
    int num_ytiles_;
    double tile_width_;
    double tile_height_;
};

#endif // TILESHEET_H
