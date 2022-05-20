#ifndef HEROSTATE_H
#define HEROSTATE_H

#include <QHash>
#include <QObject>
#include <QVariant>

class HeroState : public QObject
{
    Q_OBJECT
public:
    explicit HeroState(QObject* parent = nullptr);

    void InitState(const QHash<QString, double>& data);

    void EndRound();
    void PrepareAction();

Q_SIGNALS:
    void SgnBattleStateChange();

public:
    QHash<QString, double> ability_state_; // 能力属性
    QHash<QString, double> battle_state_; // 战斗属性
};

#endif // HEROSTATE_H
