#ifndef HERO_H
#define HERO_H

#include "data/cell.h"

#include <QPointer>

class HeroSprite;
class SceneManager;

struct HeroProperties
{
    int xing_dong_li { 0 }; // 行动力
    int surplus_xing_dong_li { 0 }; // 行动力
    double xu_li_speed { 0 }; // 蓄力速度

    double max_xue_liang { 0 }; // 最大血量
};

struct HeroState // 英雄状态
{
    double xue_liang { 0 }; // 血量
    double xu_li { 0 }; // 蓄力值
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
    void SetCell(const Cell& new_cell);
    Cell GetCell() const;
    void SetPos(const QPointF& pos);

    // 跑进度条
    void ActionTimeAdvance();
    double GetActionProgess();
    void ActionTimeReset();

    // 获取当前可移动范围
    QList<Cell> GetMovingRange() const;
    QList<Cell> GetAttackRange() const;
    QList<Cell> GetMovingTrack(const Cell& new_cell) const;
    bool CanMoveToCell(Cell cell) const;
    void SetTargetCell(Cell cell);
    Cell GetTargetCell() const;
    bool ConsumeXingDongLi(int data);

    QString BasePropertiesStr() const;

    SceneManager* GetSceneManager() const;

    void SetOperate(const bool& operate);

private:
    void InitialState();

    void UpdataHeroSpriteState();

private:
    Cell cell_, target_cell_;
    HeroSprite* sprite_;

    HeroProperties base_properties_; // 基本属性
    HeroState hero_state_; //  英雄状态

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
