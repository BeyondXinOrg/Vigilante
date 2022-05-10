#ifndef HERO_H
#define HERO_H

#include "data/cell.h"

#include <QPointer>

class HeroSprite;
class SceneManager;

struct HeroProperties
{
    short action_force { 0 }; // 行动力
    short agile { 0 }; // 敏捷
    short speed { 0 }; // 速度

    short physical_attack { 0 }; // 物理攻击
    short physical_defense { 0 }; // 物理防御

    short max_blood { 0 }; // 最大血量
};

struct HeroState // 英雄状态
{
    short blood { 0 }; // 血量
    double action_progress { 0 };
};

enum BattleState // 战斗状态
{
    KEnergy_Storage, // 蓄力（跑进度条）
    KSelection_Destination, // 选择移动位置
    KConfirm_Destination, // 确认移动位置
    KSelection_Hero, // 选择对象(攻击、用药)
};

class Hero : public QObject
{
    Q_OBJECT
public:
    // 初始化
    Hero();
    ~Hero();
    void SetHeroSprite(HeroSprite* sprite);
    HeroSprite* GetSprite() const;
    void SetBattle(SceneManager* mgr);

    // 设置位置
    void MoveToCell(const Cell& new_cell);
    void SetCell(const Cell& new_cell);
    Cell GetCell() const;
    // 跑进度条
    void ActionTimeAdvance();
    double GetActionProgess();
    void ActionTimeReset();
    // 战斗状态
    void SetBattleState(const BattleState& state);
    BattleState GetBattleState() const;

    // 获取当前可移动范围
    QList<Cell> GetMovingRange() const;
    QList<Cell> GetMovingTrack(const Cell& new_cell) const;
    bool CanMoveToCell(Cell cell) const;
    void SetTargetCell(Cell cell);
    Cell GetTargetCell() const;

    QString BasePropertiesStr() const;

private:
    void InitialState();
    void TmpUpState();

private:
    Cell cell_, target_cell_;
    HeroSprite* sprite_;

    HeroProperties base_properties_; // 基本属性
    HeroState hero_state_; //  英雄状态
    BattleState battle_state_; // 战斗状态

    SceneManager* scene_mgr_;
};

inline uint qHash(const QPointer<Hero>& key, uint seed)
{
    return qHash(key.data(), seed);
}

inline QDebug operator<<(QDebug dbg, const Hero& hero)
{
    return dbg
      << QString("Hero(%1,%2)")
           .arg(hero.GetCell().x)
           .arg(hero.GetCell().y);
}

inline QDebug operator<<(QDebug dbg, const Hero* hero)
{
    return dbg
      << QString("Hero(%1,%2)")
           .arg(hero->GetCell().x)
           .arg(hero->GetCell().y);
}

#endif // HERO_H
