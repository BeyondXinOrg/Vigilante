#ifndef BALLTLEMANAGER_H
#define BALLTLEMANAGER_H

class SceneManager;
class ColourfulMapBlock;
class BriefPropertyPanel;
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

    void WaitOperationHero(Hero* hero);
    void WaitAIOperationHero(Hero* hero);
    void EndOperationHero(Hero* hero);

private:
    SceneManager* scene_mgr_;

    ColourfulMapBlock* ui_colourful_map_block_;
    BriefPropertyPanel* ui_brief_property_;

    CellGrid* cell_grid_;

    QHash<Hero*, Camp> heros_;
    QPointer<Hero> cur_hero_;

    QTimer* battle_timer_;
};

#endif // BALLTLEMANAGER_H
