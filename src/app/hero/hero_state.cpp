#pragma execution_character_set("utf-8")

#include "hero_state.h"

#include <QDebug>

HeroState::HeroState(QObject* parent)
  : QObject { parent }
{
}

// 设置战斗属性
void HeroState::InitState(const QHash<QString, double>& data)
{
    ability_state_.clear();
    ability_state_ = data;

    battle_state_["HP"] = ability_state_.value("HP");
    battle_state_["蓄力值"] = 0;
    battle_state_["行动力"] = ability_state_.value("移动");
    battle_state_["攻击"] = ability_state_.value("力量");
    battle_state_["防守"] = ability_state_.value("防守");

    emit SgnBattleStateChange();
}

// 结束回合
void HeroState::EndRound()
{
    battle_state_["蓄力值"] = 0;
    battle_state_["行动力"] = ability_state_.value("移动");

    emit SgnBattleStateChange();
}

// 蓄力
void HeroState::PrepareAction()
{
    battle_state_["蓄力值"] += ability_state_.value("蓄力");
    emit SgnBattleStateChange();
}
