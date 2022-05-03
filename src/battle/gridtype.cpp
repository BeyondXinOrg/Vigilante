#include "gridtype.h"

Tile::Tile()
{
}

NormalTile::NormalTile(Cell& cell)
{
    cell_ = cell;
}

bool NormalTile::CanMove()
{
    return true;
}

int NormalTile::Consumption()
{
    return 1;
}

bool TreeTIle::CanMove()
{
    return true;
}

int TreeTIle::Consumption()
{
    return 1;
}

bool RockTIle::CanMove()
{
    return false;
}

int RockTIle::Consumption()
{
    return 1;
}
