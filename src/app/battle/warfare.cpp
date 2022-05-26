#pragma execution_character_set("utf-8")

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
    delete panel_mgr_;
    delete operate_mgr_;
    delete round_mgr_;
}

void Battle::BeginWar()
{
    scene_mgr_->Launch();
    round_mgr_->EndRound();
    AudiosManager::Instance()->PlayBg(bg_music_key_);
}

// 回合英雄改变
void Battle::OnChangeRoundHero(Hero* hero)
{
    operate_mgr_->SetOperateHero(hero);
    panel_mgr_->ChangeDescription(hero->GetCell());
}

// 场景点击
void Battle::OnSceneClick()
{
    auto click_cell = scene_mgr_->GetCurMouseCell();

    if (operate_mgr_->CanHandelClick()) {
        operate_mgr_->ClickedPosition(click_cell);
    }

    if (operate_mgr_->CanOperate()) {
        panel_mgr_->ChangeDescription(round_mgr_->GetRoundHero()->GetCell());
        panel_mgr_->ChangeTerrainDescription(click_cell);
    } else {
        panel_mgr_->ChangeDescription(click_cell);
    }
}

// 定位当前回合英雄
void Battle::OnLoactionRoundHero()
{
    operate_mgr_->SetOperateHero(round_mgr_->GetRoundHero());
    panel_mgr_->ChangeDescription(round_mgr_->GetRoundHero()->GetCell());
}

// 回合英雄操作结束
void Battle::OnEndOperate()
{
    // 清空操作、提示面板
    operate_mgr_->ClearDecorate();
    panel_mgr_->ClearDecorate();

    round_mgr_->EndRound();
}

// 英雄在移动或者攻击
void Battle::OnMoveOrAttack()
{
    // 清空操作、提示面板
    operate_mgr_->ClearDecorate();
    panel_mgr_->ClearDecorate();
}

void Battle::GenerateScene(int x, int y, QString bg_pix_path)
{
    cell_grid_ = new CellGrid(x, y);
    scene_mgr_ = new SceneManager(cell_grid_, 128);
    scene_mgr_->SetSceneMap(bg_pix_path);
    diplomacy_mgr_ = new DiplomacyManager();
    panel_mgr_ = new UIPanelManager(scene_mgr_);
    operate_mgr_ = new OperateManager(scene_mgr_);
    round_mgr_ = new RoundManager();

    connect(scene_mgr_, &SceneManager::SgnMouseRelease, this, &Battle::OnSceneClick);
    connect(round_mgr_, &RoundManager::SgnRoundHeroChange, this, &Battle::OnChangeRoundHero);
    connect(operate_mgr_, &OperateManager::SgnLocationOperateHero, this, &Battle::OnLoactionRoundHero);
    connect(operate_mgr_, &OperateManager::SgnEndOperate, this, &Battle::OnEndOperate);
    connect(operate_mgr_, &OperateManager::SgnMoveOrAttack, this, &Battle::OnMoveOrAttack);
    connect(operate_mgr_, &OperateManager::SgnEndMoveOrAttack, this, &Battle::OnLoactionRoundHero);
}
