#ifndef HEROCONTROLLER_H
#define HEROCONTROLLER_H

#include "hero/hero.h"

class HeroController : public QObject
{
    Q_OBJECT
public:
    HeroController(Hero* hero);
    virtual ~HeroController() override;

    Hero* HeroControlled();
    void SetHeroControlled(Hero* hero);

protected:
    QPointer<Hero> hero_controlled_;
};

#endif // HEROCONTROLLER_H
