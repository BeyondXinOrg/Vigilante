#ifndef HCPATHMOVER_H
#define HCPATHMOVER_H

#include "data/cell.h"
#include "hero/hero_controller.h"

class HCPathMover : public HeroController
{
    Q_OBJECT
public:
    HCPathMover(Hero* hero = nullptr);

    void MoveHero(const QList<Cell>& paths);
    bool IsMoving();

    void StopMoveHero();

Q_SIGNALS:
    void SgnSuccesfullyMoved(HCPathMover* by_mover);

private:
    void OnMoveStep();

private:
    bool is_moving_;

    int step_size_;

    QList<QPointF> path_pos_;
    QList<QString> orientation_list_;

    int target_point_index_;

    Cell target_cell_;

    QTimer* move_timer_;
};

#endif // HCPATHMOVER_H
