#ifndef WARFARE_H
#define WARFARE_H

#include <QHash>
#include <QObject>

class CellGrid;
class SceneManager;
class DiplomacyManager;
class HeroPanelManager;
class OperateManager;
class RoundManager;
class Hero;

namespace QXlsx {
class Document;
}

class Battle : public QObject
{
    Q_OBJECT
    friend class GenerateBattle;

public:
    void BeginWar();

private:
    Battle();
    ~Battle() override;

    void OnChangeRoundHero(Hero* hero);
    void OnSceneClick();
    void OnLoactionRoundHero();
    void OnEndOperate();

    void GenerateScene(int x, int y, QString bg_pix_path);

private:
    CellGrid* cell_grid_;
    SceneManager* scene_mgr_;

    DiplomacyManager* diplomacy_mgr_;
    HeroPanelManager* heropanel_mgr_;
    OperateManager* operate_mgr_;
    RoundManager* round_mgr_;

    QString bg_music_key_;
};

#endif // WARFARE_H
