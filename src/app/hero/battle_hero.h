#ifndef BATTLEHERO_H
#define BATTLEHERO_H

#include "hero/hero.h"

class Battle;

struct BattleHeroState
{
    double xue_liang { 0 }; // 血量
    double xu_li { 0 }; // 蓄力值
};

class BattleHero : public QObject
{
    Q_OBJECT
public:
    BattleHero();

private:
    Hero* hero_;
    Battle* battle_;
};

#endif // BATTLEHERO_H
