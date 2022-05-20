#pragma execution_character_set("utf-8")

#include "hero.h"

#include "hero/hero_sprite.h"
#include "hero/hero_state.h"
#include "scene/path_grid.h"
#include "scene/path_map.h"
#include "scene/scene_manager.h"

#include <QRandomGenerator>

Hero::Hero()
{
    scene_mgr_ = nullptr;
    sprite_ = nullptr;
    state_ = nullptr;
}

Hero::~Hero()
{
}

void Hero::SetBattle(SceneManager* mgr)
{
    Q_ASSERT(sprite_);
    Q_ASSERT(state_);

    scene_mgr_ = mgr;
    sprite_->setParentItem(scene_mgr_->GetHerosLayer());
    SetCell(cell_);
}

// 设置精灵
void Hero::SetHeroSprite(HeroSprite* sprite)
{
    sprite->setParent(this);
    sprite_ = sprite;
    sprite_->setParent(this);
}

// 设置属性
void Hero::SetHeroState(HeroState* state)
{
    state->setParent(this);
    state_ = state;
    connect(state_, &HeroState::SgnBattleStateChange,
            this, &Hero::UpdataHeroSpriteState);
}

HeroSprite* Hero::Sprite() const
{
    return sprite_;
}

HeroState* Hero::State() const
{
    return state_;
}

// 设置位置
void Hero::SetCell(const Cell& new_cell)
{
    cell_ = new_cell;

    if (scene_mgr_ && sprite_ != nullptr) {
        sprite_->SetSpritePos(scene_mgr_->GetPathGrid()->CellToPoint(cell_));
        scene_mgr_->UpdataPathMap();
    }
}

// 设置位置
Cell Hero::GetCell() const
{
    return cell_;
}

// 播放动画用
void Hero::SetPos(const QPointF& pos)
{
    if (scene_mgr_ && sprite_ != nullptr) {
        sprite_->SetSpritePos(pos);
    }
}

QList<Cell> Hero::GetMovingRange() const
{
    const int move_size = state_->battle_state_.value("行动力");
    auto path_map = scene_mgr_->GetPathMap();
    return path_map->CanReachPath(GetCell(), move_size);
}

QList<Cell> Hero::GetAttackRange() const
{
    const int move_size = state_->battle_state_.value("行动力");
    auto path_map = scene_mgr_->GetPathMap();
    auto moving_range = path_map->CanReachPath(GetCell(), move_size);
    moving_range << GetCell();
    QSet<Cell> attack_range;
    foreach (auto cell, moving_range) {
        attack_range << cell + Cell(0, 1);
        attack_range << cell + Cell(0, -1);
        attack_range << cell + Cell(1, 0);
        attack_range << cell + Cell(-1, 0);
    }
    attack_range.remove(GetCell());

    return QList<Cell>(attack_range.begin(), attack_range.end());
}

QList<Cell> Hero::GetMovingTrack(const Cell& new_cell) const
{
    const int can_move_size = state_->ability_state_.value("移动");
    auto path_map = scene_mgr_->GetPathMap();
    auto cells = path_map->MovingPath(GetCell(), can_move_size, new_cell);

    return cells;
}

bool Hero::CanMoveToCell(Cell cell) const
{
    const int move_size = state_->battle_state_.value("行动力");
    auto path_map = scene_mgr_->GetPathMap();
    auto cells = path_map->CanReachPath(GetCell(), move_size);
    return cells.contains(cell);
}

void Hero::SetTargetCell(Cell cell)
{
    target_cell_ = cell;
}

Cell Hero::GetTargetCell() const
{
    return target_cell_;
}

bool Hero::ConsumeXingDongLi(int data)
{
    const int move_size = state_->battle_state_.value("行动力");
    if (move_size >= data) {
        state_->battle_state_["行动力"] = move_size - data;
        return true;
    }
    return false;
}

QString Hero::BasePropertiesStr() const
{
    QString str;
    return str;
}

SceneManager* Hero::GetSceneManager() const
{
    return scene_mgr_;
}

void Hero::SetOperate(const bool& operate)
{
    sprite_->SetOperate(operate);
}

// 更新英雄精灵状态（血槽、蓄力槽）
void Hero::UpdataHeroSpriteState()
{
    const double data1 = state_->battle_state_.value("蓄力值") / 100.0;
    const double data2 = state_->battle_state_.value("HP")
      / state_->ability_state_.value("HP");
    sprite_->UpdataState(data1, data2);
}
