﻿#include "warfare.h"

#include "scene/scene_manager.h"

#include "diplomacy_manager.h"
#include "hero/hero.h"
#include "hero/hero_sheet.h"
#include "hero/hero_sprite.h"
#include "warfare/hero_panel_manager.h"
#include "warfare/operate_manager.h"
#include "warfare/round_manager.h"

#include <QApplication>
#include <QThread>
#include <QTimer>

Hero* CreateHero(int x, int y, QString png)
{
    Hero* hero = new Hero();
    HeroSheet* hero_sheet = new HeroSheet(png, 16, 3, 64, 64);
    HeroSprite* hero_sprite = new HeroSprite();

    hero_sprite->AddAnimation("death_down", hero_sheet->TileAt(Cell(0, 0), Cell(1, 0)));

    hero_sprite->AddAnimation("attack_up", hero_sheet->TileAt(Cell(12, 1), Cell(15, 1)));
    hero_sprite->AddAnimation("attack_down", hero_sheet->TileAt(Cell(0, 1), Cell(3, 1)));
    hero_sprite->AddAnimation("attack_left", hero_sheet->TileAt(Cell(4, 1), Cell(7, 1)));
    hero_sprite->AddAnimation("attack_right", hero_sheet->TileAt(Cell(8, 1), Cell(11, 1)));

    hero_sprite->AddAnimation("move_up", hero_sheet->TileAt(Cell(12, 2), Cell(15, 2)));
    hero_sprite->AddAnimation("move_down", hero_sheet->TileAt(Cell(0, 2), Cell(3, 2)));
    hero_sprite->AddAnimation("move_left", hero_sheet->TileAt(Cell(4, 2), Cell(7, 2)));
    hero_sprite->AddAnimation("move_right", hero_sheet->TileAt(Cell(8, 2), Cell(11, 2)));

    hero_sprite->AddAnimation("stand_up", hero_sheet->TileAt(Cell(12, 2), Cell(13, 2)));
    hero_sprite->AddAnimation("stand_down", hero_sheet->TileAt(Cell(0, 2), Cell(1, 2)));
    hero_sprite->AddAnimation("stand_left", hero_sheet->TileAt(Cell(4, 2), Cell(5, 2)));
    hero_sprite->AddAnimation("stand_right", hero_sheet->TileAt(Cell(8, 2), Cell(9, 2)));

    hero->SetHeroSprite(hero_sprite);
    hero_sprite->PlayAnimation("stand_down");

    hero->SetCell(Cell(x, y));
    return hero;
}

Warfare::Warfare()
{
    cell_grid_ = new CellGrid(22, 15);
    scene_mgr_ = new SceneManager(cell_grid_, 128);

    diplomacy_mgr_ = new DiplomacyManager();
    heropanel_mgr_ = new HeroPanelManager(scene_mgr_);
    operate_mgr_ = new OperateManager(scene_mgr_);
    round_mgr_ = new RoundManager();

    InitConnect();

    QList<Hero*> heros;
    Hero* hero;
    hero = CreateHero(0, 0, u8"./sheet_舞女.png");
    heros << hero;
    hero = CreateHero(0, 1, u8"./sheet_弓骑兵.png");
    heros << hero;
    hero = CreateHero(9, 9, u8"./sheet_关羽骑马.png");
    heros << hero;
    hero = CreateHero(9, 8, u8"./sheet_张飞骑马.png");
    heros << hero;

    foreach (auto var, heros) {
        if (scene_mgr_->AddHero(var)) {
            round_mgr_->AddHero(var);
        };
    }
}

void Warfare::BeginWar()
{
    scene_mgr_->Launch();
    round_mgr_->EndRound();
}

void Warfare::InitConnect()
{
    connect(scene_mgr_, &SceneManager::SgnMouseRelease, this, &Warfare::OnSceneClick);

    connect(round_mgr_, &RoundManager::SgnRoundHeroChange, this, &Warfare::OnChangeRoundHero);
    connect(operate_mgr_, &OperateManager::SgnLocationOperateHero, this, &Warfare::OnLoactionRoundHero);
    connect(operate_mgr_, &OperateManager::SgnEndOperate, this, &Warfare::OnEndOperate);
}

// 回合英雄改变
void Warfare::OnChangeRoundHero(Hero* hero)
{
    operate_mgr_->SetOperateHero(hero);
    heropanel_mgr_->ChangeShowHero(hero);
}

// 场景点击
void Warfare::OnSceneClick()
{
    auto click_cell = scene_mgr_->GetCurMouseCell();
    operate_mgr_->ClickedPosition(click_cell);
    if (operate_mgr_->CanOperate()) {
        heropanel_mgr_->ChangeShowHero(round_mgr_->GetRoundHero());
    } else {
        heropanel_mgr_->ChangeShowHero(click_cell);
    }
}

// 定位当前回合英雄
void Warfare::OnLoactionRoundHero()
{
    operate_mgr_->SetOperateHero(round_mgr_->GetRoundHero());
    heropanel_mgr_->ChangeShowHero(round_mgr_->GetRoundHero());
}

// 回合英雄操作结束
void Warfare::OnEndOperate()
{
    heropanel_mgr_->ClearHero();
    round_mgr_->EndRound();
}
