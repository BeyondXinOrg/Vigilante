#include "hc_path_mover.h"

#include "hero/hero_sprite.h"
#include "scene/path_grid.h"
#include "scene/scene_manager.h"

#include <QTimer>

HCPathMover::HCPathMover(Hero* hero)
  : HeroController(hero)
{
    is_moving_ = false;

    move_timer_ = new QTimer(this);
    step_size_ = 10;
}

void HCPathMover::MoveHero(const QList<Cell>& paths)
{
    StopMoveHero();

    if (!hero_controlled_) {
        return;
    }

    auto scene_mgr = hero_controlled_->GetSceneManager();
    auto path_grid = scene_mgr->GetPathGrid();

    path_pos_.clear();
    orientation_list_.clear();

    for (int i = 0; i < paths.size() - 1; i++) {
        const QPointF pos1 = path_grid->CellToPoint(paths.at(i));
        const QPointF pos2 = path_grid->CellToPoint(paths.at(i + 1));
        const double offset_x = (pos2 - pos1).x() / step_size_;
        const double offset_y = (pos2 - pos1).y() / step_size_;
        const QPointF offset(offset_x, offset_y);
        for (int k = 0; k < step_size_; k++) {
            path_pos_ << pos1 + k * offset;
        }
        if (offset_x > 0.1) {
            orientation_list_ << "right";
        } else if (offset_x < -0.1) {
            orientation_list_ << "left";
        } else if (offset_y > 0.1) {
            orientation_list_ << "down";
        } else if (offset_y < -0.1) {
            orientation_list_ << "up";
        }
    }
    target_cell_ = paths.last();
    target_point_index_ = 0;

    connect(move_timer_, &QTimer::timeout, this, &HCPathMover::OnMoveStep);
    move_timer_->start(25);
}

bool HCPathMover::IsMoving()
{
    return is_moving_;
}

void HCPathMover::StopMoveHero()
{
    move_timer_->disconnect();
    move_timer_->stop();
    is_moving_ = false;
}

void HCPathMover::OnMoveStep()
{
    if (!hero_controlled_) {
        return;
    }

    if (target_point_index_ >= path_pos_.size()) {
        hero_controlled_->SetCell(target_cell_);
        StopMoveHero();
        QString name = "stand_" + orientation_list_.last();
        hero_controlled_->GetSprite()->PlayAnimation(name);
        emit SgnSuccesfullyMoved(this);
        return;
    }

    QString name = "move_" + orientation_list_.at(target_point_index_ / step_size_);
    auto cur_animation = hero_controlled_->GetSprite()->CurAnimation();
    if (name != cur_animation) {
        hero_controlled_->GetSprite()->PlayAnimation(name);
    }

    hero_controlled_->SetPos(path_pos_.at(target_point_index_));
    target_point_index_++;
}
