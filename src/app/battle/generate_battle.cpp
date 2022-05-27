#pragma execution_character_set("utf-8")

#include "generate_battle.h"

#include "audios/audios_manager.h"
#include "battle/battle.h"
#include "battle/hero_panel_manager.h"
#include "battle/operate_manager.h"
#include "battle/round_manager.h"
#include "data/cell.h"
#include "diplomacy_manager.h"
#include "hero/hero.h"
#include "hero/hero_sheet.h"
#include "hero/hero_sprite.h"
#include "hero/hero_state.h"
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
    QString battle_map_key, heros_str;
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
    heros_str = LoadConfigCell(battle_row, 3).toString();

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
    auto heros_str_list = heros_str.split(";");
    foreach (auto hero_str, heros_str_list) {
        auto hero_str_list = hero_str.split(",");

        QString hero_key = hero_str_list.at(1);
        Hero* hero = CreateHero(hero_key);

        Cell pos(hero_str_list.at(2).toInt(), hero_str_list.at(3).toInt());
        hero->SetCell(pos);

        if (warfare->scene_mgr_->AddHero(hero)) {
            warfare->round_mgr_->AddHero(hero);
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

Hero* GenerateBattle::CreateHero(QString key)
{
    Hero* hero = new Hero();

    xlsx_r_->selectSheet("人物");
    auto xlsx_r_ange = xlsx_r_->dimension();
    int row = -1;
    for (int i = 1; i <= xlsx_r_ange.rowCount(); ++i) {
        QXlsx::Cell* key_cell = xlsx_r_->cellAt(i, 1);
        if (key_cell != nullptr && key_cell->readValue().toString() == key) {
            row = i;
            break;
        } else {
            continue;
        }
    }

    if (row <= 0) {
        return nullptr;
    }

    QString animation_png = LoadConfigCell(row, 3).toString();
    QString state_key = LoadConfigCell(row, 6).toString();
    QString hero_name = LoadConfigCell(row, 2).toString();

    hero->SetHeroState(CreateHeroState(state_key));
    hero->SetHeroSprite(CreateHeroSprite(resources_.value(animation_png)));
    hero->State()->name_ = hero_name;
    return hero;
}

HeroSprite* GenerateBattle::CreateHeroSprite(QString png)
{
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

    hero_sprite->PlayAnimation("stand_down");
    return hero_sprite;
}

HeroState* GenerateBattle::CreateHeroState(QString key)
{
    QHash<QString, double> data;

    xlsx_r_->selectSheet("能力属性");
    auto xlsx_r_ange = xlsx_r_->dimension();
    int row = -1;
    for (int i = 1; i <= xlsx_r_ange.rowCount(); ++i) {
        QXlsx::Cell* key_cell = xlsx_r_->cellAt(i, 1);
        if (key_cell != nullptr && key_cell->readValue().toString() == key) {
            row = i;
            break;
        } else {
            continue;
        }
    }

    if (row <= 0) {
        return nullptr;
    }

    for (int i = 1; i <= xlsx_r_ange.columnCount(); ++i) {
        data[LoadConfigCell(1, i).toString()] = LoadConfigCell(row, i).toDouble();
    }

    HeroState* state = new HeroState();
    state->InitState(data);
    return state;
}
