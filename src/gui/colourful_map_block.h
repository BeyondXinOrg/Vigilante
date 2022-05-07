#ifndef COLOURFULMAPBLOCK_H
#define COLOURFULMAPBLOCK_H

#include "data/cell.h"
#include "gui.h"

#include <QBrush>
#include <QHash>
#include <QPen>

class ColourfulMapBlock : public Gui
{
    Q_OBJECT
public:
    enum Type
    {
        KHover_Block_Type, // 格子：鼠标高亮

        KCurHero_Bolock_Type, // 格子：当前英雄位置
        KCurHero_Range_Type, // 格子：当前英雄移动范围

        KPlayer_Camp_Type, // 格子：玩家阵营
        KEnemy_Camp_Type, // 格子：敌对阵营
    };

public:
    ColourfulMapBlock();

    QGraphicsItem* GetGraphicsItem() override;
    void SetSceneManager(SceneManager* scene_mgr) override;

    void ShowCurHeroBlock(const Cell& cur_cell);
    void HideCurHeroBlock();

    void ShowMovingRangeBlock(const QList<Cell>& cells = {});

    void UpdataCampBlock(const QList<Cell>& player_cell,
                         const QList<Cell>& enemy_cell);

private:
    void FollowMouse();

private:
    QGraphicsRectItem* center_item_;

    QTimer* follow_timer_;

    QHash<Type, QList<QGraphicsRectItem*>> blocks_;
    QHash<Type, QPen> blocks_brush_;

    QRectF cell_rect_;
};

#endif // COLOURFULMAPBLOCK_H
