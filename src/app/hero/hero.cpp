#include "hero.h"

#include "hero/hero_sprite.h"
#include "scene/path_grid.h"
#include "scene/path_map.h"
#include "scene/scene_manager.h"

#include <QRandomGenerator>

Hero::Hero()
{
    scene_mgr_ = nullptr;
    InitialState();
}

Hero::~Hero()
{
}

HeroSprite* Hero::GetSprite() const
{
    return sprite_;
}

void Hero::SetBattle(SceneManager* mgr)
{
    scene_mgr_ = mgr;
    if (sprite_) {
        sprite_->setParentItem(scene_mgr_->GetHerosLayer());
    }
    SetCell(cell_);
}

void Hero::SetHeroSprite(HeroSprite* sprite)
{
    //    if (map_) { // 如果实体已在地图中
    //        sprite_->underlying_item_->setParentItem(nullptr);
    //        sprite->underlying_item_->setParentItem(map_->GetHerosLayer());
    //        SetCell(cell_); // 确保新精灵在场景中的位置正确
    //    }

    // 设置内部精灵\指向新精灵的指针
    sprite_ = sprite;
    sprite_->setParent(this);
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

// 跑进度条
void Hero::ActionTimeAdvance()
{
    hero_state_.xu_li += base_properties_.xu_li_speed;
    UpdataHeroSpriteState();
}

double Hero::GetActionProgess()
{
    return hero_state_.xu_li;
}

void Hero::ActionTimeReset()
{
    hero_state_.xu_li = 0.0;
    base_properties_.surplus_xing_dong_li = base_properties_.xing_dong_li;
    UpdataHeroSpriteState();
}

QList<Cell> Hero::GetMovingRange() const
{
    auto path_map = scene_mgr_->GetPathMap();
    return path_map->CanReachPath(GetCell(), base_properties_.surplus_xing_dong_li);
}

QList<Cell> Hero::GetAttackRange() const
{
    auto path_map = scene_mgr_->GetPathMap();
    auto moving_range = path_map->CanReachPath(GetCell(), base_properties_.surplus_xing_dong_li);
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
    auto path_map = scene_mgr_->GetPathMap();
    auto cells = path_map->MovingPath(
      GetCell(), base_properties_.xing_dong_li, new_cell);

    return cells;
}

bool Hero::CanMoveToCell(Cell cell) const
{
    auto path_map = scene_mgr_->GetPathMap();
    auto cells = path_map->CanReachPath(
      GetCell(),
      base_properties_.surplus_xing_dong_li);
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
    if (base_properties_.surplus_xing_dong_li >= data) {
        base_properties_.surplus_xing_dong_li -= data;
        return true;
    }
    return false;
}

QString Hero::BasePropertiesStr() const
{
    QString str;

    str += QString(u8"行动力:%1  \n").arg(base_properties_.xing_dong_li);
    str += QString(u8"血量:%1  ").arg(hero_state_.xue_liang);
    str += QString(u8"进度条:%1  ").arg(hero_state_.xu_li);
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

void Hero::InitialState()
{
    // 人物基本属性
    base_properties_.xing_dong_li = 3.0;
    base_properties_.max_xue_liang = 100.0;
    base_properties_.xu_li_speed = 1.0;
    base_properties_.surplus_xing_dong_li = base_properties_.xing_dong_li;

    // 人物状态
    hero_state_.xue_liang = base_properties_.max_xue_liang;
    hero_state_.xu_li = 0;

    base_properties_.xu_li_speed += QRandomGenerator::global()->bounded(1.5);
}

// 更新英雄精灵状态
void Hero::UpdataHeroSpriteState()
{
    sprite_->UpdataState(
      hero_state_.xu_li / 100.0,
      hero_state_.xue_liang / base_properties_.max_xue_liang);
}
