#ifndef BALLTLEMANAGER_H
#define BALLTLEMANAGER_H

class SceneManager;
class BriefPropertyPanel;
class GUIlocationHero;
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
    void InitConnect();
    void BattleTimeAdvance();
    void WaitOperationHero(Hero* hero);
    void WaitAIOperationHero(Hero* hero);
    void EndOperationHero(Hero* hero);

    void OnSceneCellSelect();

private:
    SceneManager* scene_mgr_;
    BriefPropertyPanel* ui_brief_property_;
    GUIlocationHero* ui_location_hero_;

    CellGrid* cell_grid_;

    QHash<Hero*, Camp> heros_;
    QPointer<Hero> cur_hero_;
    QPointer<Hero> select_hero_;

    QTimer* battle_timer_;
};

#endif // BALLTLEMANAGER_H
