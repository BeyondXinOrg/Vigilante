#include "battle_manager.h"

#include "battle/battle_view.h"
#include "battle/layout_terrain.h"
#include "battle/path_grid.h"
#include "battle/tile_sheet.h"

BattleManager::BattleManager(QObject* parint)
  : QObject(parint)
  , view_(new BattleView())
  , scene_(new QGraphicsScene(this))
  , data_(new PathGrid(24, 24, 32))

  , lay_terrain_(new LayoutTerrain())

{
    tile_sheet_ = new TileSheet("C:\\Users\\77935\\Desktop/2.png", 1, 5, 22, 22);
    tile_sheet_->SetTileCell(Cell(0, 0), KTreeTIle);
    tile_sheet_->SetTileCell(Cell(1, 0), KRockTIle);
    tile_sheet_->SetTileCell(Cell(2, 0), KNormalTile);
    tile_sheet_->SetTileCell(Cell(3, 0), KNormalTile1);
    tile_sheet_->SetTileCell(Cell(4, 0), KNormalTile2);

    scene_->setSceneRect(0, 0, data_->Width(), data_->Height());

    lay_terrain_->Resize(data_->Width(), data_->Height());
    lay_terrain_->SetData(data_);
    lay_terrain_->SetTileSheetData(tile_sheet_);
    scene_->addItem(lay_terrain_);

    QBrush bb;
    bb.setStyle(Qt::SolidPattern);
    bb.setColor(Qt::black);
    scene_->setBackgroundBrush(bb);

    view_->setScene(scene_);
}

void BattleManager::Launch()
{
    view_->setFixedSize(1920, 1080);
    view_->showNormal();
}
