#include "diplomacy_manager.h"

DiplomacyManager::DiplomacyManager()
{
}

Relationship DiplomacyManager::GetRelationship(int group1, int group2)
{
    if (group1 == group2) {
        return Relationship::kREL_Friend;
    }

    return Relationship::kREL_Friend;
}

void DiplomacyManager::AddHero(int group, Heros* hero)
{
    groups_hero_[group] << hero;
}
