#ifndef LAYOUTTERRAIN_H
#define LAYOUTTERRAIN_H

#include <QGraphicsItem>

class TileSheet;
class TerrainMap;
class PathGrid;

class LayoutTerrain : public QGraphicsItem
{
public:
    LayoutTerrain(QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const override;

    void Resize(int width, int heigh);
    void SetPathGrid(PathGrid* data);
    void SetTileSheetData(TileSheet* data);
    void SetTerrainMap(TerrainMap* data);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item,
               QWidget* widget) override;

    void UpdataTerrainBg();

private:
    QRectF rect_;

    PathGrid* path_grid_;
    TileSheet* tile_sheet_;
    TerrainMap* terrain_map_;

    QPixmap bg_pix_;
};

#endif // LAYOUTTERRAIN_H
