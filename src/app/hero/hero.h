#ifndef HERO_H
#define HERO_H

#include "data/cell.h"

#include <QPointer>

class HeroSprite;
class SceneManager;
class HeroState;

class Hero : public QObject
{
    Q_OBJECT
public:
    // 初始化
    Hero();
    ~Hero();

    void SetBattle(SceneManager* mgr);
    void SetHeroSprite(HeroSprite* sprite);
    void SetHeroState(HeroState* state);
    HeroSprite* Sprite() const;
    HeroState* State() const;

    // 设置位置
    void SetCell(const Cell& new_cell);
    Cell GetCell() const;
    void SetPos(const QPointF& pos);

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

    void SetAbilityState(const QString& data);

private:
    void UpdataHeroSpriteState();

private:
    SceneManager* scene_mgr_;
    HeroSprite* sprite_;
    HeroState* state_;

    Cell cell_, target_cell_;

    QHash<QString, QVariant> ability_state_; // 能力属性
    QHash<QString, QVariant> battle_state_; // 战斗属性
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
