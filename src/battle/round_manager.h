#ifndef ROUNDMANAGER_H
#define ROUNDMANAGER_H

class Hero;
class QTimer;

#include <QPointer>

class RoundManager : public QObject
{
    Q_OBJECT
public:
    RoundManager();

    void AddHero(Hero* hero);
    void RemoveHero(Hero* hero);

    Hero* GetRoundHero();

    void EndRound();

Q_SIGNALS:
    void SgnRoundHeroChange(Hero* hero = nullptr);

private:
    void OnTimerAdvance();

private:
    QList<Hero*> heros_;
    QPointer<Hero> round_hero_;

    QTimer* timer_speed_;
};

#endif // ROUNDMANAGER_H
