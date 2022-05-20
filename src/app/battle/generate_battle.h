#ifndef GENERATEBATTLE_H
#define GENERATEBATTLE_H

#include <QHash>
#include <QObject>

class Battle;
class HeroSprite;
class Hero;
class HeroState;
namespace QXlsx {
class Document;
}

class GenerateBattle : public QObject
{
    Q_OBJECT
public:
    GenerateBattle(const QString& config_name = "./config.xlsx");

    Battle* GetBattle(const QString& battle_name = u8"测试战斗");

private:
    QVariant LoadConfigCell(int col, int row);
    void LoadConfigResources();

    Hero* CreateHero(QString key);
    HeroSprite* CreateHeroSprite(QString png);
    HeroState* CreateHeroState(QString key);

private:
    QHash<QString, QString> resources_;
    QXlsx::Document* xlsx_r_;
};

#endif // GENERATEBATTLE_H
