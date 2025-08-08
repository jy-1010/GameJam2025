#include "../../Utility/Utility.h"
#include "../../Scene/Game/GameScene.h"
#include "../UI/LifeUI.h"
#include "CPU.h"

CPU::CPU(GameScene& gameScene, int playerNum, VECTOR pos) : PlayerBase(gameScene,playerNum, pos)
{
	//CPUの状態遷移処理を登録
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
	if (isInvincible_) { return; }	//無敵状態ならダメージを受けない
	isInvincible_ = true;	//無敵状態にする
	hp_--;
	lifeUI_->SetLife(hp_);	//ライフUIに現在のHPを設定
	if (hp_ <= 0)
	{
		gameScene_.PlayerDeath(playerNum_);	//プレイヤーの死亡処理を行う
		ChengeState(STATE::DEATH);	//HPが0以下なら死亡状態へ
		return;
	}
	else
	{
		deathVec_ = Utility::VNormalize(vec);	//死亡時のベクトルを設定
		ChengeState(STATE::DAMAGE);
		return;
	}
}

void CPU::UpdateLand(void)
{
	if (GetRand(RANDAM_MAX) / static_cast<float>(RANDAM_MAX) < JUMP_RATE)
	{
		ChengeState(STATE::JUMP);	//ランダムでジャンプ状態へ遷移
	}
}

void CPU::UpdateJump(void)
{

	deceleration_ += JUMP_DECELERATION;	//減速率を増加させる
	pos_.y += JUMP_SPEED - deceleration_;	//上昇速度から減速率を引く

	if (GetRand(RANDAM_MAX) / static_cast<float>(RANDAM_MAX) < DROP_RATE)
	{
		waveSpeedType_ = static_cast<Wave::SPEED_TYPE>(GetRand(static_cast<int>(Wave::SPEED_TYPE::MAX) - 1));	//ランダムで波の速度を決定
		ChengeState(STATE::ROAL);
	}

	if (pos_.y < 0.0f)
	{
		pos_.y = 0.0f;
		ChengeState(STATE::LAND);
	}
}
