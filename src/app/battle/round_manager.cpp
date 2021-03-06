#pragma execution_character_set("utf-8")

#include "round_manager.h"

#include "hero/hero.h"
#include "hero/hero_state.h"

#include <QTimer>

RoundManager::RoundManager()
{
    timer_speed_ = new QTimer(this);
    connect(timer_speed_, &QTimer::timeout,
            this, &RoundManager::OnTimerAdvance);
}

void RoundManager::AddHero(Hero* hero)
{
    if (heros_.contains(hero)) {
        return;
    }

    heros_ << hero;
}

void RoundManager::RemoveHero(Hero* hero)
{
    if (!heros_.contains(hero)) {
        return;
    }

    heros_.removeOne(hero);
}

Hero* RoundManager::GetRoundHero()
{
    return round_hero_;
}

void RoundManager::EndRound()
{
    if (round_hero_) {
        round_hero_->SetOperate(false);
        round_hero_->State()->EndRound();
        round_hero_ = nullptr;
    }
    timer_speed_->start(15);
}

void RoundManager::OnTimerAdvance()
{
    // 检测英雄进度
    foreach (auto hero, heros_) {
        double progress = hero->State()->battle_state_.value("蓄力值");
        if (progress >= 100) {
            timer_speed_->stop();
            round_hero_ = hero;
            round_hero_->SetOperate(true);
            emit SgnRoundHeroChange(round_hero_);
            return;
        }
    }

    if (round_hero_) {
        round_hero_ = nullptr;
        emit SgnRoundHeroChange(round_hero_);
    }

    // 英雄行动进度推进
    foreach (auto hero, heros_) {
        hero->State()->PrepareAction();
    }
}
