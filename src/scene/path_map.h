#ifndef PATHMAP_H
#define PATHMAP_H

#include "data/cell_grid.h"

class PathMap
{
public:
    PathMap(CellGrid* grid);

    void Fill();
    void Fill(const Cell& cell);
    void UnFill();
    void UnFill(const Cell& cell);

    bool Filled(const Cell& cell) const;

private:
    CellGrid* grid_;
    QHash<Cell, bool> filled_;
};

#endif // PATHMAP_H
