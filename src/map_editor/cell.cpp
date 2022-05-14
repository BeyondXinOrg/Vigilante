#include "cell.h"

Cell::Cell()
  : x(0)
  , y(0)
{
}

Cell::Cell(const Cell& cell)
  : x(cell.x)
  , y(cell.y)
{
}

Cell::Cell(short tmp_x, short tmp_y)
  : x(tmp_x)
  , y(tmp_y)
{
}
