#ifndef TERRAINMAP_H
#define TERRAINMAP_H

#include "data/cell_grid.h"

enum TerrainType
{
    KNormal_Cell = 0,
    KTree_Cell = 10,
    KWall_Cell = 50,
};

class RandomForest
{
public:
    RandomForest();

    QList<Cell> GetForest(int id = -1) const;
    int RandomForestSize(int min = 2, int max = 8);

private:
    QList<QList<Cell>> tree_types_;
};

class TerrainMap
{
public:
    TerrainMap(int num_cols, int num_rows);
    TerrainMap(CellGrid* grid);

    QList<TerrainType> GetAllTerrainType() const;
    QList<Cell> GetTerrainCell(const TerrainType& type) const;

    QList<Cell> GetWallTerrainCell() const;

private:
    void GenerateRandomTerrain();
    void SmoothWallWayMap(int wall_bound = 4, int way_bound = 4);

    void RefreshTypesCell();

private:
    QHash<Cell, TerrainType> cells_type_;
    QHash<TerrainType, QList<Cell>> types_cell_;

    RandomForest random_forest_;
    CellGrid* grid_;
};

#endif // TERRAINMAP_H
