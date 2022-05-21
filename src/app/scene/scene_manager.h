#ifndef SceneManager_H
#define SceneManager_H

#include "hero/hero.h"
#include "scene/layout_terrain.h"

#include <QObject>

class View;
class QGraphicsScene;
class QGraphicsRectItem;
class PathGrid;
class LayoutTerrain;
class CellGrid;
class PathGrid;
class PathMap;
class Gui;
class TerrainDecoration;

class SceneManager : public QObject
{
    Q_OBJECT
public:
    SceneManager(CellGrid* cell_grid, int cell_size, QObject* parint = nullptr);

    // 设置地图
    void SetSceneMap(const QString& pix_path);
    // 设置人物
    bool AddHero(Hero* hero);
    void RemoveHero(Hero* hero);
    // 设置ui
    void AddGui(Gui* gui);
    // 设置地形装饰
    void AddTerrainDecoration(TerrainDecoration* td);
    // 战斗开始
    void Launch();

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
    QGraphicsRectItem* lay_terrain_decoration_;
    QGraphicsRectItem* lay_heros_;
    QGraphicsRectItem* lay_gui_;

    QSet<Hero*> heros_;
};

#endif // BATTLEMANAGER_H
