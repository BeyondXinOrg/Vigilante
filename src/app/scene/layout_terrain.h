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

class LayoutTerrain : public QGraphicsItem
{
public:
    LayoutTerrain(QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const override;

    void Resize(int width, int heigh);
    void SetSceneMap(const QString& pix_path);
    TerrainType GetTerrainType(const Cell& cell);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item,
               QWidget* widget) override;

private:
    QRectF rect_;

    QHash<Cell, TerrainType> cells_type_;

    QPixmap bg_pix_;
};

#endif // LAYOUTTERRAIN_H
