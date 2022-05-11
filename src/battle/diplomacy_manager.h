#ifndef DIPLOMACYMANAGER_H
#define DIPLOMACYMANAGER_H

#include <QHash>

// 目前只有两个阵营，非友即敌。后续拓展
enum class Relationship
{
    kREL_Friend,
    kREL_Enemy,
    kREL_None,
};

class Heros;

class DiplomacyManager
{
public:
    DiplomacyManager();

    Relationship GetRelationship(int group1, int group2);

    void AddHero(int group, Heros* hero);

private:
    QHash<int, QList<Heros*>> groups_hero_;
    QHash<std::pair<int, int>, Relationship> pair_relationship_;
};

#endif // DIPLOMACYMANAGER_H
