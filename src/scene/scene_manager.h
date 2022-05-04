#ifndef SceneManager_H
#define SceneManager_H

#include "hero/hero.h"

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
class TerrainMap;
class Gui;

class SceneManager : public QObject
{
    Q_OBJECT
public:
    SceneManager(CellGrid* cell_grid, int cell_size, QObject* parint = nullptr);

    void Launch();

    void AddHero(Hero* hero);
    void RemoveHero(Hero* hero);

    QGraphicsRectItem* GetHerosLayer() const;
    QGraphicsRectItem* GetGuiLayer() const;
    PathGrid* GetPathGrid();

    void UpdataPathMap();

    Cell GetCurMouseCell() const;

    void AddGui(Gui* gui);

private:
    View* view_;
    QGraphicsScene* scene_;

    // 网格数据
    CellGrid* cell_grid_;

    PathGrid* path_grid_;
    PathMap* path_map_;
    TerrainMap* terrain_map_;

    LayoutTerrain* lay_terrain_;
    QGraphicsRectItem* lay_heros_;
    QGraphicsRectItem* lay_gui_;

    QSet<Hero*> heros_;

    TileSheet* tile_sheet_;
};

#endif // BATTLEMANAGER_H
