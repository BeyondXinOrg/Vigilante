#ifndef TDCOLOURFULCELL_H
#define TDCOLOURFULCELL_H

#include "data/cell_grid.h"
#include "terrain_decoration/terrain_decoration.h"

#include <QGraphicsItem>
#include <QPen>

class Hero;

class TDColourfulCell : public TerrainDecoration, public QGraphicsItem
{
public:
    TDColourfulCell();
    ~TDColourfulCell() override;

    QGraphicsItem* GetGraphicsItem() override;
    void SetSceneManager(SceneManager* scene_mgr) override;
    QRectF boundingRect() const override;

    void SetSelectHero(Hero* hero);
    void SetSelectCell(const Cell& cell);

    void SetMovingTrack(QList<Cell> cells);
    void HideMovingTrack();

    void ClearSelect();

protected:
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* item,
               QWidget* widget) override;
    void UpdataTerrainBg();

private:
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

#endif // TDCOLOURFULCELL_H
