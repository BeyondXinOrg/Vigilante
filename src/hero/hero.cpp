#include "hero.h"

#include "hero/hero_sprite.h"
#include "scene/path_grid.h"
#include "scene/scene_manager.h"

Hero::Hero()
{
    batle_mgr_ = nullptr;
    InitialState();
}

Hero::~Hero()
{
}

void Hero::SetCell(const Cell& new_cell)
{
    cell_ = new_cell;

    if (batle_mgr_ && sprite_ != nullptr) {
        sprite_->SetSpritePos(batle_mgr_->GetPathGrid()->CellToPoint(cell_));
    }
}

Cell Hero::GetCell() const
{
    return cell_;
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
}

void Hero::InitialState()
{
    base_properties_.action_force = 3;
    base_properties_.agile = 12;
    base_properties_.physical_attack = 50;
    base_properties_.physical_defense = 3;
    base_properties_.max_blood = 100;

    state_.blood = base_properties_.max_blood;
    state_.action_progress = 0;
}
