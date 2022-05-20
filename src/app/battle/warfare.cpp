﻿#pragma execution_character_set("utf-8")

#include "warfare.h"

#include "audios/audios_manager.h"
#include "battle/hero_panel_manager.h"
#include "battle/operate_manager.h"
#include "battle/round_manager.h"
#include "diplomacy_manager.h"
#include "hero/hero.h"
#include "hero/hero_sheet.h"
#include "hero/hero_sprite.h"
#include "scene/scene_manager.h"

#include "QXlsx/header/xlsxcellrange.h"
#include "QXlsx/header/xlsxchart.h"
#include "QXlsx/header/xlsxchartsheet.h"
#include "QXlsx/header/xlsxdocument.h"
#include "QXlsx/header/xlsxrichstring.h"
#include "QXlsx/header/xlsxworkbook.h"

#include <QApplication>
#include <QThread>
#include <QTimer>

Battle::Battle()
{
}

Battle::~Battle()
{
    delete cell_grid_;
    delete scene_mgr_;
    delete diplomacy_mgr_;
    delete heropanel_mgr_;
    delete operate_mgr_;
    delete round_mgr_;
}

void Battle::BeginWar()
{
    scene_mgr_->Launch();
    round_mgr_->EndRound();

    //    AudiosManager::Instance()->PlayBg(bg_music_key_);
}

// 回合英雄改变
void Battle::OnChangeRoundHero(Hero* hero)
{
    operate_mgr_->SetOperateHero(hero);
}

// 场景点击
void Battle::OnSceneClick()
{
    if (!operate_mgr_->CanHandelClick()) {
        return;
    }

    auto click_cell = scene_mgr_->GetCurMouseCell();
    operate_mgr_->ClickedPosition(click_cell);
}

// 定位当前回合英雄
void Battle::OnLoactionRoundHero()
{
    operate_mgr_->SetOperateHero(round_mgr_->GetRoundHero());
}

// 回合英雄操作结束
void Battle::OnEndOperate()
{
    round_mgr_->EndRound();
}

void Battle::GenerateScene(int x, int y, QString bg_pix_path)
{
    cell_grid_ = new CellGrid(x, y);
    scene_mgr_ = new SceneManager(cell_grid_, 128);
    scene_mgr_->SetSceneMap(bg_pix_path);
    diplomacy_mgr_ = new DiplomacyManager();
    heropanel_mgr_ = new HeroPanelManager(scene_mgr_);
    operate_mgr_ = new OperateManager(scene_mgr_);
    round_mgr_ = new RoundManager();

    connect(scene_mgr_, &SceneManager::SgnMouseRelease, this, &Battle::OnSceneClick);
    connect(round_mgr_, &RoundManager::SgnRoundHeroChange, this, &Battle::OnChangeRoundHero);
    connect(operate_mgr_, &OperateManager::SgnLocationOperateHero, this, &Battle::OnLoactionRoundHero);
    connect(operate_mgr_, &OperateManager::SgnEndOperate, this, &Battle::OnEndOperate);
}
