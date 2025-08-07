#include "CPU.h"

CPU::CPU(int playerNum, VECTOR pos) : PlayerBase(playerNum, pos)
{
	//CPU‚Ìó‘Ô‘JˆÚˆ—‚ğ“o˜^
	stateChanges_.emplace(STATE::LAND, std::bind(&CPU::UpdateLand, this));
	stateChanges_.emplace(STATE::JUMP, std::bind(&CPU::UpdateJump, this));
	//stateChanges_.emplace(STATE::ROAL, std::bind(&PlayerBase::ChengeStateRoal, this));
	//stateChanges_.emplace(STATE::DROP, std::bind(&PlayerBase::ChengeStateDrop, this));
	//stateChanges_.emplace(STATE::DAMAGE, std::bind(&PlayerBase::ChengeStateDamage, this));
	//stateChanges_.emplace(STATE::DEATH, std::bind(&PlayerBase::ChengeStateDeath, this));
}

CPU::~CPU(void)
{
	//PlayerBase::~PlayerBase();
}

void CPU::UpdateLand(void)
{
	if (GetRand(RANDAM_MAX) / static_cast<float>(RANDAM_MAX) < JUMP_RATE)
	{
		ChengeState(STATE::JUMP);	//ƒ‰ƒ“ƒ_ƒ€‚ÅƒWƒƒƒ“ƒvó‘Ô‚Ö‘JˆÚ
	}
}

void CPU::UpdateJump(void)
{

	deceleration_ += JUMP_DECELERATION;	//Œ¸‘¬—¦‚ğ‘‰Á‚³‚¹‚é
	pos_.y += JUMP_SPEED - deceleration_;	//ã¸‘¬“x‚©‚çŒ¸‘¬—¦‚ğˆø‚­

	if (GetRand(RANDAM_MAX) / static_cast<float>(RANDAM_MAX) < DROP_RATE)
	{
		waveSpeedType_ = static_cast<Wave::SPEED_TYPE>(GetRand(static_cast<int>(Wave::SPEED_TYPE::MAX) - 1));	//ƒ‰ƒ“ƒ_ƒ€‚Å”g‚Ì‘¬“x‚ğŒˆ’è
		ChengeState(STATE::ROAL);
	}

	if (pos_.y < 0.0f)
	{
		pos_.y = 0.0f;
		ChengeState(STATE::LAND);
	}
}
