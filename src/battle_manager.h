#ifndef BALLTLEMANAGER_H
#define BALLTLEMANAGER_H

class SceneManager;
class ColourfulMapBlock;
class CellGrid;
class Hero;

#include <QHash>
#include <QPointer>

class BattleManager : public QObject
{
    Q_OBJECT
public:
    enum Camp
    {
        KPlayer = 0,
        KEnemy = 1,
    };

public:
    BattleManager();

    void Launch();

private:
    void UpdataCampBlock();

    void BattleTimeAdvance();

private:
    SceneManager* scene_mgr_;
    ColourfulMapBlock* colourful_map_block_;

    CellGrid* cell_grid_;

    QHash<Hero*, Camp> heros_;
    QPointer<Hero> cur_hero_;

    QTimer* battle_timer_;
};

#endif // BALLTLEMANAGER_H
