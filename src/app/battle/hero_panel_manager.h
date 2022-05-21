#ifndef HEROPANELMANAGER_H
#define HEROPANELMANAGER_H

#include "data/cell.h"

#include <QHash>
#include <QPointer>

class SceneManager;
class BriefPropertyPanel;
class GuiTerrainDescription;
class Hero;

class UIPanelManager : public QObject
{
    Q_OBJECT
public:
    UIPanelManager(SceneManager* scene_mgr);
    void ClickedPosition(const Cell& cell);

    void ClearDecorate();

private:
    SceneManager* scene_mgr_;
    GuiTerrainDescription* ui_terrain_description_;

    QPointer<Hero> cur_hero_;
};

#endif // HEROPANELMANAGER_H
