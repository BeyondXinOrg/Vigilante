#ifndef HEROPANELMANAGER_H
#define HEROPANELMANAGER_H

#include "data/cell.h"

#include <QHash>
#include <QPointer>

class Hero;
class QTimer;
class SceneManager;
class GUIlocationHero;
class GUISkipRound;

class HeroPanelManager : public QObject
{
    Q_OBJECT
public:
    HeroPanelManager(SceneManager* scene_mgr);

    void ChangeShowHero(Hero* hero);
    void ChangeShowHero(Cell click_cell);

    void ClearHero();

private:
    SceneManager* scene_mgr_;
    QPointer<Hero> cur_hero_;
};

#endif // HEROPANELMANAGER_H
