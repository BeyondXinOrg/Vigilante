#ifndef HEROPANELMANAGER_H
#define HEROPANELMANAGER_H

#include "data/cell.h"

#include <QHash>
#include <QPointer>

class SceneManager;
class BriefPropertyPanel;
class GuiTerrainDescription;
class GuiHeroDescription;
class Hero;

class UIPanelManager : public QObject
{
    Q_OBJECT
public:
    UIPanelManager(SceneManager* scene_mgr);

    void ChangeDescription(const Cell& cell);
    void ChangeTerrainDescription(const Cell& cell);
    void ChangeHeroDescription(const Cell& cell);

    void ClearDecorate();

Q_SIGNALS:
    void SgnClickedSkill(int id);

private:
    SceneManager* scene_mgr_;
    GuiTerrainDescription* ui_terrain_description_;
    GuiHeroDescription* ui_hero_description_;

    QPointer<Hero> cur_hero_;
};

#endif // HEROPANELMANAGER_H
