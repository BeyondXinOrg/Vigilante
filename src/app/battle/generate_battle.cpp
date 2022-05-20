#pragma execution_character_set("utf-8")

#include "generate_battle.h"

#include "audios/audios_manager.h"
#include "battle/hero_panel_manager.h"
#include "battle/operate_manager.h"
#include "battle/round_manager.h"
#include "battle/warfare.h"
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

Hero* CreateHero(int x, int y, QString png);

GenerateBattle::GenerateBattle(const QString& config_name)
{
    xlsx_r_ = new QXlsx::Document(config_name, this);
    Q_ASSERT(xlsx_r_->load());
    LoadConfigResources();
}

// 生成一个battle
Battle* GenerateBattle::GetBattle(const QString& battle_name)
{
    Battle* warfare = new Battle();

    // 解析战斗
    QString battle_map_key;
    QStringList armys;
    xlsx_r_->selectSheet("战斗");
    auto xlsx_r_ange = xlsx_r_->dimension();
    int battle_row = -1;
    for (int row = 1; row <= xlsx_r_ange.rowCount(); ++row) {
        QXlsx::Cell* key = xlsx_r_->cellAt(row, 1);
        if (key != nullptr && key->readValue().toString() == battle_name) {
            battle_row = row;
            break;
        } else {
            continue;
        }
    }
    if (battle_row <= 0) {
        return nullptr;
    }
    battle_map_key = LoadConfigCell(battle_row, 2).toString();
    armys << LoadConfigCell(battle_row, 3).toString();
    armys << LoadConfigCell(battle_row, 4).toString();

    // 解析战斗场景
    xlsx_r_->selectSheet("战斗地图");
    xlsx_r_ange = xlsx_r_->dimension();
    int battle_map_row = -1;
    for (int row = 1; row <= xlsx_r_ange.rowCount(); ++row) {
        QXlsx::Cell* key = xlsx_r_->cellAt(row, 1);
        if (key != nullptr && key->readValue().toString() == battle_map_key) {
            battle_map_row = row;
            break;
        } else {
            continue;
        }
    }
    if (battle_map_row <= 0) {
        return nullptr;
    }

    QString background, terrain, bg_music_key;
    int xblocks, yblocks;
    background = LoadConfigCell(battle_row, 2).toString();
    bg_music_key = LoadConfigCell(battle_row, 3).toString();
    xblocks = LoadConfigCell(battle_row, 4).toInt();
    yblocks = LoadConfigCell(battle_row, 5).toInt();
    terrain = LoadConfigCell(battle_row, 6).toString();

    // 加载音乐
    AudiosManager::Instance()->LoadBgMusic(bg_music_key, resources_.value(bg_music_key));
    warfare->bg_music_key_ = bg_music_key;

    // 生成地图
    warfare->GenerateScene(xblocks, yblocks, resources_.value(background));

    // 地图增加人物
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
        if (warfare->scene_mgr_->AddHero(var)) {
            warfare->round_mgr_->AddHero(var);
        };
    }

    return warfare;
}

// 读取当前单元格（不切换sheet）
QVariant GenerateBattle::LoadConfigCell(int row, int col)
{
    QXlsx::Cell* cell = xlsx_r_->cellAt(row, col);
    if (cell != nullptr) {
        return cell->readValue();
    }
    return "";
}

// 读取游戏资源
void GenerateBattle::LoadConfigResources()
{
    resources_.clear();
    xlsx_r_->selectSheet("资源");
    auto xlsx_r_ange = xlsx_r_->dimension();
    for (int row = 1; row <= xlsx_r_ange.rowCount(); ++row) {
        QString key, value;
        QXlsx::Cell* key_cell = xlsx_r_->cellAt(row, 1);
        QXlsx::Cell* value_cell = xlsx_r_->cellAt(row, 2);
        if (key_cell != nullptr && value_cell != nullptr) {
            key = key_cell->readValue().toString();
            value = value_cell->readValue().toString();
        } else {
            continue;
        }
        resources_[key] = value;
    }
}

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
