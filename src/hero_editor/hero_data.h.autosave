#ifndef HERODATA_H
#define HERODATA_H

#include <QHash>
#include <QStringList>
#include <QVariant>

// enum HeroVocation
//{
//     Swordsman,
//     soldiers
// };

class HeroData
{
public:
    int level_; // 等级
    QString hero_name_; // 名称
    QString animation_; // 动画
    QString vocation_; // 职业

    QHash<QString, QVariant> ability_state_; // 能力属性
    QHash<QString, QVariant> battle_state_; // 战斗属性

public:
    static void CalculateBattleState(HeroData& data);
};

#endif // HERODATA_H
