#ifndef TILESHEET_H
#define TILESHEET_H

#include <QHash>
#include <QPixmap>

#include "battle/gridtype.h"
#include "data/cell.h"

class TileSheet
{
public:
    TileSheet(QString file_path,
              int num_xtiles,
              int num_ytiles,
              double tile_width,
              double tile_height);

    QPixmap TileAt(const TileType& type) const;
    void SetTileCell(const Cell& cell, const TileType& type);

private:
    QPixmap pixmap_;
    QHash<TileType, QPixmap> tiles_;

    int num_xtiles_;
    int num_ytiles_;
    double tile_width_;
    double tile_height_;
};

#endif // TILESHEET_H
