#ifndef GRIDTYPE_H
#define GRIDTYPE_H

#include "data/cell.h"

enum TileType
{
    KNormalTile = 0,
    KNormalTile1 = 1,
    KNormalTile2 = 2,
    KTreeTIle = 10,
    KRockTIle = 50,
};

class Tile
{

public:
    Tile();

    virtual bool CanMove() = 0;
    virtual int Consumption() = 0;

protected:
    Cell cell_;
};

class NormalTile : public Tile
{
public:
    NormalTile(Cell& cell);

    bool CanMove() override;
    int Consumption() override;
};

class TreeTIle : public Tile
{
public:
    TreeTIle(Cell& cell);

    bool CanMove() override;
    int Consumption() override;
};

class RockTIle : public Tile
{
public:
    RockTIle(Cell& cell);

    bool CanMove() override;
    int Consumption() override;
};

#endif // GRIDTYPE_H
