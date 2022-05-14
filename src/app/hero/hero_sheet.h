#ifndef HEROSHEET_H
#define HEROSHEET_H

#include "data/cell_grid.h"

#include <QPixmap>

class HeroSheet
{
public:
    HeroSheet(const QString str, int x, int y, int w, int h);

    QPixmap TileAt(const Cell& cell) const;
    QList<QPixmap> TileAt(const Cell& tl, const Cell& bd) const;

private:
    CellGrid* sheet_grid_;
    QPixmap pixmap_;
    int w_, h_;
};

#endif // HEROSHEET_H
