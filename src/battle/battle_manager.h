#ifndef BATTLEMANAGER_H
#define BATTLEMANAGER_H

#include <QObject>

class BattleView;
class QGraphicsScene;
class QGraphicsRectItem;
class TileSheet;
class PathGrid;
class LayoutTerrain;

class BattleManager : public QObject
{
    Q_OBJECT
public:
    BattleManager(QObject* parint = nullptr);

    void Launch();

private:
    BattleView* view_;
    QGraphicsScene* scene_;

    PathGrid* data_;

    LayoutTerrain* lay_terrain_;
    QGraphicsRectItem* lay_heros_;
    QGraphicsRectItem* lay_gui_;

    TileSheet* tile_sheet_;
};

#endif // BATTLEMANAGER_H
