#include "hero_data.h"

void HeroData::CalculateBattleState(HeroData& data)
{
    data.battle_state_["xue_liang"] = data.ability_state_.value("HP");
    data.battle_state_["gong_ji"] = data.ability_state_.value("li_liang");
    data.battle_state_["fang_shou"] = data.ability_state_.value("fang_shou");
}

// data.battle_state_["ming_zhong"] = data.ability_state_.value("");
// data.battle_state_["bi_sha"] = data.ability_state_.value("");
// data.battle_state_["gong_su"] = data.ability_state_.value("");
// data.battle_state_["hui_bi"] = data.ability_state_.value("");
// data.battle_state_["nai_mo"] = data.ability_state_.value("");
// data.battle_state_["she_cheng"] = data.ability_state_.value("");
// data.battle_state_["yi_dong"] = data.ability_state_.value("");
