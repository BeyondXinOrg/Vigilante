#ifndef PATHMAP_H
#define PATHMAP_H

#include "data/cell_grid.h"
#include "data/graph.h"

class PathMap
{
public:
    PathMap(CellGrid* grid);

    void Fill();
    void Fill(const Cell& cell);
    void UnFill();
    void UnFill(const Cell& cell);

    bool Filled(const Cell& cell) const;

    Graph PartGridToGraph(const Cell& from, const int& power) const;
    QList<Cell> CanReachPath(const Cell& from, const int& power) const;

private:
    CellGrid* grid_;
    QHash<Cell, bool> filled_;
};

#endif // PATHMAP_H
