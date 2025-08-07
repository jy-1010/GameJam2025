#include "../../Utility/Utility.h"
#include "../../Manager/Input/KeyConfig.h"
#include "PlayerBase.h"

PlayerBase::PlayerBase(int playerNum,VECTOR pos)
{
	playerNum_ = playerNum;
	color_ = playerNum == 0 ? Utility::RED : playerNum == 1 ? Utility::BLUE : playerNum == 2 ? Utility::YELLOW : Utility::GREEN;
	pos_ = pos;
	initPos_=pos_;
	hp_ = MAX_HP;

	//ÉtÉFÅ[ÉYÇÃèÛë‘ëJà⁄èàóùÇìoò^
	stateChanges_.emplace(STATE::LAND, std::bind(&PlayerBase::ChengeStateLand, this));
	stateChanges_.emplace(STATE::JUMP, std::bind(&PlayerBase::ChengeStateJump, this));
	stateChanges_.emplace(STATE::ROAL , std::bind(&PlayerBase::ChengeStateRoal, this));
	stateChanges_.emplace(STATE::DROP, std::bind(&PlayerBase::ChengeStateDrop, this));
	stateChanges_.emplace(STATE::DAMAGE, std::bind(&PlayerBase::ChengeStateDamage, this));
	stateChanges_.emplace(STATE::DEATH, std::bind(&PlayerBase::ChengeStateDeath, this));

	ChengeState(STATE::LAND);
}

PlayerBase::~PlayerBase(void)
{
}

void PlayerBase::Init(void)
{
}

void PlayerBase::Update(void)
{
	stateUpdate_();
}

void PlayerBase::Draw(void)
{
}

void PlayerBase::Damage(void)
{
	hp_--;
	ChengeState(STATE::DAMAGE);
}

void PlayerBase::UpdateLand(void)
{
	
}

void PlayerBase::UpdateJump(void)
{
}

void PlayerBase::UpdateRoal(void)
{
}

void PlayerBase::UpdateDrop(void)
{
}

void PlayerBase::UpdateDamage(void)
{
}

void PlayerBase::UpdateDeath(void)
{
}

void PlayerBase::ChengeState(STATE state)
{
	state_ = state;
	stateChanges_[state_];
}

void PlayerBase::ChengeStateLand(void)
{
	stateUpdate_ = std::bind(&PlayerBase::UpdateLand, this);
}

void PlayerBase::ChengeStateJump(void)
{
	stateUpdate_ = std::bind(&PlayerBase::UpdateJump, this);
}

void PlayerBase::ChengeStateRoal(void)
{
	stateUpdate_ = std::bind(&PlayerBase::UpdateRoal, this);
}

void PlayerBase::ChengeStateDrop(void)
{
	stateUpdate_ = std::bind(&PlayerBase::UpdateDrop, this);
}

void PlayerBase::ChengeStateDamage(void)
{
}

void PlayerBase::ChengeStateDeath(void)
{
}

void PlayerBase::MakeWave(Wave::SPEED_TYPE speedType)
{
	std::shared_ptr<Wave> wave;
	wave = std::make_shared<Wave>(initPos_, speedType, color_);
}
