#include "../../Utility/Utility.h"
#include "../../Scene/Game/GameScene.h"
#include "../UI/LifeUI.h"
#include "CPU.h"

CPU::CPU(GameScene& gameScene, int playerNum, VECTOR pos) : PlayerBase(gameScene,playerNum, pos)
{
	//CPU�̏�ԑJ�ڏ�����o�^
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

void CPU::Damage(VECTOR vec)
{
	if (isInvincible_) { return; }	//���G��ԂȂ�_���[�W���󂯂Ȃ�
	isInvincible_ = true;	//���G��Ԃɂ���
	hp_--;
	lifeUI_->SetLife(hp_);	//���C�tUI�Ɍ��݂�HP��ݒ�
	if (hp_ <= 0)
	{
		gameScene_.PlayerDeath(playerNum_);	//�v���C���[�̎��S�������s��
		ChengeState(STATE::DEATH);	//HP��0�ȉ��Ȃ玀�S��Ԃ�
		return;
	}
	else
	{
		deathVec_ = Utility::VNormalize(vec);	//���S���̃x�N�g����ݒ�
		ChengeState(STATE::DAMAGE);
		return;
	}
}

void CPU::UpdateLand(void)
{
	if (GetRand(RANDAM_MAX) / static_cast<float>(RANDAM_MAX) < JUMP_RATE)
	{
		ChengeState(STATE::JUMP);	//�����_���ŃW�����v��Ԃ֑J��
	}
}

void CPU::UpdateJump(void)
{

	deceleration_ += JUMP_DECELERATION;	//�������𑝉�������
	pos_.y += JUMP_SPEED - deceleration_;	//�㏸���x���猸����������

	if (GetRand(RANDAM_MAX) / static_cast<float>(RANDAM_MAX) < DROP_RATE)
	{
		waveSpeedType_ = static_cast<Wave::SPEED_TYPE>(GetRand(static_cast<int>(Wave::SPEED_TYPE::MAX) - 1));	//�����_���Ŕg�̑��x������
		ChengeState(STATE::ROAL);
	}

	if (pos_.y < 0.0f)
	{
		pos_.y = 0.0f;
		ChengeState(STATE::LAND);
	}
}
