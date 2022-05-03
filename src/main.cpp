#include <QApplication>

#include "battle/battle_manager.h"

//#include "game.h"
//#include "hero.h"
//#include "hero_sprite.h"
//#include "heroattribute.h"
//#include "map_block_follow_mouse.h"
//#include "map_game.h"
//#include "roundsystemcontrol.h"
//#include "sprite_sheet.h"

// Hero* GetHero(GameMap* map, QString str, int x, int y)
//{
//     Hero* hero = new Hero();

//    SpriteSheet sprite_sheet(str, 4, 4, 32, 50);

//    HeroSprite* hero_sprite = new HeroSprite();
//    hero->SetHeroSprite(hero_sprite);
//    hero->SetCell(x, y);

//    for (int i = 0, n = 4; i < n; ++i) {
//        int angle = (0 + 90 * i) % 360;
//        hero_sprite->AddFrames(angle, "stand", sprite_sheet, Node(0, 0 + i), Node(3, 0 + i));
//    }

//    hero_sprite->Play("stand");
//    hero_sprite->SetFaceAngle(180);

//    return hero;
//}

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    BattleManager battle;
    battle.Launch();
    //    GameMap* map = new GameMap(20, 20, 100);

    //    Game* game = new Game(map);
    //    game->Launch();

    //    auto sys_control = new RoundSystemControl();
    //    sys_control->SetMapGame(map);
    //    sys_control->AddPlayerHero(GetHero(map, ":/resources/hero/002.png", 6, 6));
    //    sys_control->AddPlayerHero(GetHero(map, ":/resources/hero/002.png", 6, 7));
    //    sys_control->AddEnemyHero(GetHero(map, ":/resources/hero/003.png", 1, 1));
    //    sys_control->AddEnemyHero(GetHero(map, ":/resources/hero/004.png", 6, 5));

    //    sys_control->StartBattle();

    return a.exec();
}
