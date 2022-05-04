#ifndef BALLTLEMANAGER_H
#define BALLTLEMANAGER_H

class SceneManager;
class ColourfulMapBlock;
class CellGrid;

class BattleManager
{
public:
    BattleManager();

    void Launch();

private:
    SceneManager* scene_mgr_;
    ColourfulMapBlock* colourful_map_block_;

    CellGrid* cell_grid_;
};

#endif // BALLTLEMANAGER_H
