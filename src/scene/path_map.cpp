#include "path_map.h"

#include <QHash>

PathMap::PathMap(CellGrid* grid)
  : grid_(grid)
{
    foreach (auto cell, grid_->Cells()) {
        filled_[cell] = false;
    }
}

void PathMap::Fill()
{
    foreach (auto cell, grid_->Cells()) {
        filled_[cell] = true;
    }
}

void PathMap::Fill(const Cell& cell)
{
    filled_[cell] = true;
}

void PathMap::UnFill()
{
    foreach (auto cell, grid_->Cells()) {
        filled_[cell] = false;
    }
}

void PathMap::UnFill(const Cell& cell)
{
    filled_[cell] = false;
}

bool PathMap::Filled(const Cell& cell) const
{
    return filled_[cell];
}
