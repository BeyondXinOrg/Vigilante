#ifndef LAYOUTTERRAIN_H
#define LAYOUTTERRAIN_H

#include "data/cell_grid.h"

#include <QGraphicsItem>

class TileSheet;
class SceneManager;

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

class LayoutTerrain : public QGraphicsItem
{
public:
    LayoutTerrain(QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const override;

    void Resize(int width, int heigh);
    void SetSceneManager(SceneManager* data);
    void SetTileSheetData(TileSheet* data);
    QList<Cell> GetWallTerrainCell() const;

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item,
               QWidget* widget) override;

    void UpdataTerrainBg();

private:
    void GenerateRandomTerrain();
    void SmoothWallWayMap(int wall_bound = 4, int way_bound = 4);
    void RefreshTypesCell();

private:
    QRectF rect_;

    SceneManager* scene_mgr_;
    TileSheet* tile_sheet_;

    QHash<Cell, TerrainType> cells_type_;
    QHash<TerrainType, QList<Cell>> types_cell_;
    RandomForest random_forest_;

    QPixmap bg_pix_;
};

#endif // LAYOUTTERRAIN_H
