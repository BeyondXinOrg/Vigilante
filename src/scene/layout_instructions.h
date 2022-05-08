#ifndef LAYOUTINSTRUCTIONS_H
#define LAYOUTINSTRUCTIONS_H

#include "data/cell_grid.h"

#include <QGraphicsItem>
#include <QPen>

class Hero;
class SceneManager;

enum InstructionsMapType
{
    KCurHero_Bolock, // 格子：当前英雄位置
    KCurHero_Move_Range, // 格子：当前英雄移动范围
};

class LayoutInstructions : public QGraphicsItem
{
public:
    LayoutInstructions(QGraphicsItem* parent = nullptr);
    QRectF boundingRect() const override;

    void SetSceneManager(SceneManager* scene_mgr);
    void ChangeSelectHero(Hero* hero = nullptr);
    void ChangeSelectCell(const Cell &cell);
    void Resize(int width, int heigh);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item,
               QWidget* widget) override;
    void UpdataTerrainBg();

private:
    QRectF rect_;

    SceneManager* scene_mgr_;
    QPixmap bg_pix_;

    QBrush brush_move_range_;
    QVector<QRect> move_range_rects_;

    QBrush brush_select_;
    QRect select_rect_;
};

#endif // LAYOUTINSTRUCTIONS_H
