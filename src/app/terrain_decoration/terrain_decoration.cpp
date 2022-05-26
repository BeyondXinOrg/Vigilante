#include "terrain_decoration.h"

TerrainDecoration::TerrainDecoration()
{
}

TerrainDecoration::~TerrainDecoration()
{

}

void TerrainDecoration::SetVisable(const bool& show)
{
    GetGraphicsItem()->setVisible(show);
}
