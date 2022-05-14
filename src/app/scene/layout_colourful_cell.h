#ifndef LAYOUTCOLOURFULCELL_H
#define LAYOUTCOLOURFULCELL_H

#include "data/cell_grid.h"

#include <QGraphicsItem>
#include <QPen>

class Hero;
class SceneManager;

class LayoutColourfulCell : public QGraphicsItem
{
public:
    LayoutColourfulCell(QGraphicsItem* parent = nullptr);
    void SetSceneManager(SceneManager* scene_mgr);
    QRectF boundingRect() const override;

    void SetSelectHero(Hero* hero);
    void SetSelectCell(const Cell& cell);

    void SetMovingTrack(QList<Cell> cell);
    void HideMovingTrack();

    void ClearSelect();

protected:
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* item,
               QWidget* widget) override;
    void UpdataTerrainBg();

private:
    SceneManager* scene_mgr_;

    QPixmap bg_pix_;
    QRectF rect_;

    QBrush brush_move_range_;
    QVector<QRect> move_range_rects_;
    QBrush brush_attack_range_;
    QVector<QRect> attack_range_rects_;
    QBrush brush_select_;
    QRect select_rect_;

    bool show_move_track_;
    QList<QPointF> move_track_pos_;
};

#endif // LAYOUTCOLOURFULCELL_H
