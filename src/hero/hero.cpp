#include "hero.h"

#include "hero/hero_sprite.h"
#include "scene/path_grid.h"
#include "scene/path_map.h"
#include "scene/scene_manager.h"

#include <QRandomGenerator>

Hero::Hero()
{
    batle_mgr_ = nullptr;
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
    batle_mgr_ = mgr;
    if (sprite_) {
        sprite_->setParentItem(batle_mgr_->GetHerosLayer());
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
    TmpUpState();
}

// 设置位置
void Hero::SetCell(const Cell& new_cell)
{
    cell_ = new_cell;

    if (batle_mgr_ && sprite_ != nullptr) {
        sprite_->SetSpritePos(batle_mgr_->GetPathGrid()->CellToPoint(cell_));
    }
}

// 设置位置
Cell Hero::GetCell() const
{
    return cell_;
}

// 跑进度条
double Hero::ActionTimeAdvance()
{
    hero_state_.action_progress += 0.2 * base_properties_.agile;
    TmpUpState();
    return hero_state_.action_progress;
}

void Hero::ActionTimeReset()
{
    hero_state_.action_progress = 0;
    TmpUpState();
}

// 战斗状态
void Hero::SetBattleState(const BattleState& state)
{
    battle_state_ = state;
}

// 战斗状态
BattleState Hero::GetBattleState() const
{
    return battle_state_;
}

QList<Cell> Hero::GetMovingRange() const
{
    auto path_map = batle_mgr_->GetPathMap();
    return path_map->CanReachPath(GetCell(), base_properties_.action_force);
}

void Hero::InitialState()
{
    // 人物基本属性
    base_properties_.action_force = 3;
    base_properties_.agile = 4;
    base_properties_.physical_attack = 50;
    base_properties_.physical_defense = 3;
    base_properties_.max_blood = 100;
    base_properties_.agile += QRandomGenerator::global()->bounded(10);

    // 人物状态
    hero_state_.blood = base_properties_.max_blood;
    hero_state_.action_progress = 0;

    // 人物战斗状态
    battle_state_ = KEnergyStorage;
}

// 临时更新状态
void Hero::TmpUpState()
{
    sprite_->SetTempPreview(hero_state_.blood, hero_state_.action_progress);
}
