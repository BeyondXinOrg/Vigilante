#ifndef LAYOUTTERRAIN_H
#define LAYOUTTERRAIN_H

#include "battle/layout.h"

class TileSheet;

class LayoutTerrain : public Layout
{
public:
    LayoutTerrain(QGraphicsItem* parent = nullptr);
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* item,
               QWidget* widget) override;

    void SetTileSheetData(TileSheet* data);

private:
    TileSheet* tile_sheet_;
};

#endif // LAYOUTTERRAIN_H
