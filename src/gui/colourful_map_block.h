#ifndef COLOURFULMAPBLOCK_H
#define COLOURFULMAPBLOCK_H

#include "gui.h"

#include <QBrush>
#include <QPen>

class ColourfulMapBlock : public Gui
{
    Q_OBJECT
public:
    ColourfulMapBlock();

    QGraphicsItem* GetGraphicsItem() override;
    void SetSceneManager(SceneManager* scene_mgr) override;

private:
    void FollowMouse();

private:
    QGraphicsRectItem* center_item_;

    // 跟随鼠标移动方框
    QGraphicsRectItem* follow_item_;
    QTimer* follow_timer_;
    QBrush follow_brush_;
    QPen follow_pen_;
};

#endif // COLOURFULMAPBLOCK_H
