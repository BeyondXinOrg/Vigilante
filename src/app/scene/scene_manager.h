﻿#ifndef SceneManager_H
#define SceneManager_H

#include "hero/hero.h"
#include "scene/layout_terrain.h"

#include <QObject>

class View;
class QGraphicsScene;
class QGraphicsRectItem;
class TileSheet;
class PathGrid;
class LayoutTerrain;
class CellGrid;
class PathGrid;
class PathMap;
class Gui;
class LayoutColourfulCell;

class SceneManager : public QObject
{
    Q_OBJECT
public:
    SceneManager(CellGrid* cell_grid, int cell_size, QObject* parint = nullptr);

    void Launch();

    bool AddHero(Hero* hero);
    void RemoveHero(Hero* hero);

    QGraphicsRectItem* GetHerosLayer() const;
    QGraphicsRectItem* GetGuiLayer() const;
    CellGrid* GetCellGrid() const;
    PathGrid* GetPathGrid();
    PathMap* GetPathMap();

    void UpdataPathMap();

    Cell GetCurMouseCell() const;
    Hero* GetCurMouseHero() const;
    Hero* GetCurMouseHero(const Cell& cell) const;
    TerrainType GetTerrainType(const Cell& cell) const;
    LayoutColourfulCell* GetLayoutColourfulCell() const;

    void AddGui(Gui* gui);

    QSize GetViewSize() const;

    void MoveCamCenterToHero(Hero* hero);

Q_SIGNALS:
    void SgnMouseRelease();

private:
    void InitConnect();

private:
    View* view_;
    QGraphicsScene* scene_;

    // 网格数据
    CellGrid* cell_grid_;
    PathGrid* path_grid_;

    PathMap* path_map_;

    LayoutTerrain* lay_terrain_;
    LayoutColourfulCell* lay_colourful_cell_;
    QGraphicsRectItem* lay_heros_;

    QSet<Hero*> heros_;

    TileSheet* tile_sheet_;
};

#endif // BATTLEMANAGER_H