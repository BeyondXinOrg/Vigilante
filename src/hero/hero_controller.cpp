#include "hero_controller.h"

HeroController::HeroController(Hero* hero)
  : hero_controlled_(hero)
{
    setParent(hero);

    // listen to death
}

HeroController::~HeroController()
{
}

Hero* HeroController::HeroControlled()
{
    return hero_controlled_;
}

void HeroController::SetHeroControlled(Hero* hero)
{
    hero_controlled_ = hero;
    setParent(hero);
}
