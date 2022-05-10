#ifndef WARFARE_H
#define WARFARE_H

#include <QObject>

class CellGrid;
class SceneManager;
class DiplomacyManager;
class HeroPanelManager;
class OperateManager;
class RoundManager;
class Hero;

class Warfare : public QObject
{
    Q_OBJECT
public:
    Warfare();
    void BeginWar();

private:
    void InitConnect();

    void OnChangeRoundHero(Hero* hero);
    void OnSceneClick();
    void OnLoactionRoundHero();
    void OnEndOperate();

private:
    CellGrid* cell_grid_;
    SceneManager* scene_mgr_;

    DiplomacyManager* diplomacy_mgr_;
    HeroPanelManager* heropanel_mgr_;
    OperateManager* operate_mgr_;
    RoundManager* round_mgr_;
};

#endif // WARFARE_H
