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

    short physical_attack { 0 }; // 物理攻击
    short physical_defense { 0 }; // 物理防御

    short max_blood { 0 }; // 最大血量
};

struct HeroState
{
    short blood { 0 }; // 血量
    short action_progress { 0 };
};

class Hero : public QObject
{
    Q_OBJECT
public:
    Hero();
    ~Hero();

    void SetCell(const Cell& new_cell);
    Cell GetCell() const;
    void SetHeroSprite(HeroSprite* sprite);
    HeroSprite* GetSprite() const;

    void SetBattle(SceneManager* mgr);

private:
    void InitialState();

private:
    Cell cell_;
    HeroSprite* sprite_;

    HeroProperties base_properties_; // 基本属性
    HeroState state_; // 状态

    SceneManager* batle_mgr_;
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
