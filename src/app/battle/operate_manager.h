﻿#ifndef OPERATEMANAGER_H
#define OPERATEMANAGER_H

#include "data/cell.h"

#include <QPointer>

class Hero;
class QTimer;
class SceneManager;
class GUIlocationHero;
class GUISkipRound;
class HCPathMover;

class OperateManager : public QObject
{
    Q_OBJECT
public:
    enum OperateState
    {
        kOPE_None, // 无
        kOPE_Attack, // 攻击
        kOPE_Skill, // 释放技能
        kOPE_Moving, // 移动
        kREL_Select_Move, // 选择移动地点
        kREL_Select_Accack, // 选择移动地点
        kREL_Select_Skill_Pos, // 选择施法地点
    };

public:
    OperateManager(SceneManager* scene_mgr);

    void SetOperateHero(Hero* hero);
    void ClickedPosition(const Cell& cell);

    bool CanOperate() const;
    bool CanHandelClick() const;

    void ChangeShowHero(Hero* hero);
    void ChangeShowHero(Cell click_cell);
    void ClearHero();

Q_SIGNALS:
    void SgnEndOperate();
    void SgnLocationOperateHero();

private:
    void OnHeroEndMoving(HCPathMover* by_mover);

private:
    SceneManager* scene_mgr_;

    GUIlocationHero* ui_location_hero_;
    GUISkipRound* ui_skip_round_;

    HCPathMover* hc_path_mover_;

    QPointer<Hero> cur_hero_;
    bool can_operate_;
    Cell target_cell_;

    OperateState state_;
};

#endif // OPERATEMANAGER_H