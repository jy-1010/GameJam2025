#include <DxLib.h>
#include "../../Utility/Utility.h"
#include "../../Manager/Input/KeyConfig.h"
#include "../../Manager/Resource/ResourceManager.h"
#include "../../Manager/Resource/SoundManager.h"
#include "../../Scene/Game/GameScene.h"
#include "../UI/LifeUI.h"
#include "PlayerBase.h"

PlayerBase::PlayerBase(GameScene& gameScene, int playerNum,VECTOR pos) : gameScene_(gameScene)
{
	playerNum_ = playerNum;
	color_ = playerNum == 0 ? Utility::RED : playerNum == 1 ? Utility::BLUE : playerNum == 2 ? Utility::YELLOW : Utility::GREEN;
	pos_ = pos;
	initPos_=pos_;
	rot_ = { 0.0f, 0.0f, 0.0f };	//������]�p�x
	hp_ = MAX_HP;
	isInvincible_ = false;	//���G��Ԃ�������
	rotFlame_ = 0.0f;	//��]�t���[����
	modelId_ = ResourceManager::GetInstance().LoadModelDuplicate(
		playerNum == 0 ? ResourceManager::SRC::PLAYER_MODEL_1 :
		playerNum == 1 ? ResourceManager::SRC::PLAYER_MODEL_2 :
		playerNum == 2 ? ResourceManager::SRC::PLAYER_MODEL_3 :
		ResourceManager::SRC::PLAYER_MODEL_4);

	lifeUI_ = std::make_shared<LifeUI>(playerNum_);	//���C�tUI�𐶐�

	//�t�F�[�Y�̏�ԑJ�ڏ�����o�^
	stateChanges_.emplace(STATE::LAND, std::bind(&PlayerBase::ChengeStateLand, this));
	stateChanges_.emplace(STATE::JUMP, std::bind(&PlayerBase::ChengeStateJump, this));
	stateChanges_.emplace(STATE::ROAL , std::bind(&PlayerBase::ChengeStateRoal, this));
	stateChanges_.emplace(STATE::DROP, std::bind(&PlayerBase::ChengeStateDrop, this));
	stateChanges_.emplace(STATE::DAMAGE, std::bind(&PlayerBase::ChengeStateDamage, this));
	stateChanges_.emplace(STATE::DEATH, std::bind(&PlayerBase::ChengeStateDeath, this));
	invincibleTime_ = 0.0f;	//���G���Ԃ�������
	ChengeState(STATE::LAND);

	anime_ = std::make_shared<AnimationController>(modelId_);
	for (int i = 0; i < (int)ANIM_TYPE::MAX; i++) {
		anime_->AddInFbx(i, 30.0f, i);
	}
	anime_->Add((int)ANIM_TYPE::DANCE1, 30.0f, "Data/Model/Player/Dance1.mv1");
	anime_->Play((int)ANIM_TYPE::IDLE);
}

PlayerBase::~PlayerBase(void)
{
}

void PlayerBase::Init(void)
{
	
}

void PlayerBase::Update(void)
{
	for (auto& wave : waves)
	{
		if (wave == nullptr) { continue; }	//�g��nullptr�Ȃ�X�L�b�v
		wave->Update();
		if (wave->IsEnd())
		{
			wave = nullptr;	//�g���I�������폜
		}
	}
	anime_->Update();
	if (isInvincible_)
	{
		invincibleTime_++;
		if (invincibleTime_ > INVINCIBLE_TIME)	//���G���Ԃ��o�߂�����
		{
			invincibleTime_ = 0.0f;	//���G���Ԃ�������
			isInvincible_ = false;	//���G��Ԃ�����
		}
	}
	stateUpdate_();
	lifeUI_->SetLife(hp_);	//���C�tUI�Ɍ��݂�HP��ݒ�

	//���f���̈ʒu���X�V
	MV1SetPosition(modelId_, pos_);
	MV1SetRotationXYZ(modelId_, rot_);
}

void PlayerBase::Draw(void)
{
	for (auto& wave : waves)
	{
		if (wave == nullptr) { continue; }	//�g��nullptr�Ȃ�X�L�b�v
		wave->Draw();
	}
	//���f���`��
	MV1DrawModel(modelId_);
	//���C�tUI��`��
	lifeUI_->Draw();
}

void PlayerBase::Damage(VECTOR vec)
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

std::vector<float> PlayerBase::GetWaveRadius(void) const
{
	std::vector<float>radiuss;
	for (const auto& wave : waves)
	{
		if (wave == nullptr) { continue; }	//�g��nullptr�Ȃ�X�L�b�v
		radiuss.push_back(wave->GetRadius());
	}
	return radiuss;
}

void PlayerBase::UpdateLand(void)
{
	auto& keyCon = KeyConfig::GetInstance();
	if (keyCon.IsTrgDown(KeyConfig::CONTROL_TYPE::JUMP, static_cast<KeyConfig::JOYPAD_NO>(playerNum_ + 1)))
	{
		ChengeState(STATE::JUMP);
	}
}

void PlayerBase::UpdateJump(void)
{
	deceleration_ += JUMP_DECELERATION;	//�������𑝉�������
	pos_.y += JUMP_SPEED - deceleration_;	//�㏸���x���猸����������

	auto& keyCon = KeyConfig::GetInstance();
	if (keyCon.IsTrgDown(KeyConfig::CONTROL_TYPE::FAST_JUMP, static_cast<KeyConfig::JOYPAD_NO>(playerNum_ + 1)))
	{
		waveSpeedType_ = Wave::SPEED_TYPE::FAST;
		ChengeState(STATE::ROAL);
	}
	if (keyCon.IsTrgDown(KeyConfig::CONTROL_TYPE::SLOW_JUMP, static_cast<KeyConfig::JOYPAD_NO>(playerNum_ + 1)))
	{
		waveSpeedType_ = Wave::SPEED_TYPE::SLOW;
		ChengeState(STATE::ROAL);
	}
	if (keyCon.IsTrgDown(KeyConfig::CONTROL_TYPE::MIDIUM_JUMP, static_cast<KeyConfig::JOYPAD_NO>(playerNum_ + 1)))
	{
		waveSpeedType_ = Wave::SPEED_TYPE::MIDIUM;
		ChengeState(STATE::ROAL);
	}

	if (pos_.y < 0.0f)
	{
		pos_.y = 0.0f;
		ChengeState(STATE::LAND);
	}
}

void PlayerBase::UpdateRoal(void)
{
	rotFlame_++;
	rot_.x += Utility::Deg2RadF(360.0f / JUMP_ROAL);	//��]�p�x�𑝉�������
	if (rotFlame_ >= JUMP_ROAL)
	{
		rotFlame_ = 0.0f;	//��]�t���[������������
		ChengeState(STATE::DROP);
	}
}

void PlayerBase::UpdateDrop(void)
{
	pos_.y -= JUMP_DROP_SPEED;	//�������x������
	if (pos_.y < 0.0f)
	{
		pos_.y = 0.0f;
		MakeWave(waveSpeedType_);	//�g�𐶐�
		ChengeState(STATE::LAND);
	}
}

void PlayerBase::UpdateDamage(void)
{
	invincibleTime_++;
	if (invincibleTime_ >= DAMAGE_DELAY)	//���G���Ԃ��o�߂�����
	{
		MV1SetDifColorScale(modelId_, { 1.0f, 1.0f, 1.0f, 1.0f });//���G���Ԓ��͔�������
		if (hp_ <= 0)	//HP��0�ȉ��Ȃ玀�S��Ԃ�
		{
			ChengeState(STATE::DEATH);
		}
		else
		{
			ChengeState(STATE::LAND);	//����ȊO�͒n���Ԃ�
		}
	}
}

void PlayerBase::UpdateDeath(void)
{
	pos_ = VAdd(pos_, VScale(deathVec_, DEATH_MOVE_SPEED_XZ));	//���S���̈ړ�
	pos_.y += DEATH_MOVE_SPEED_Y;	//���S���̈ړ�
}

void PlayerBase::ChengeState(STATE state)
{
	state_ = state;
	stateChanges_[state_]();
}

void PlayerBase::ChengeStateLand(void)
{
	stateUpdate_ = std::bind(&PlayerBase::UpdateLand, this);
}

void PlayerBase::ChengeStateJump(void)
{
	deceleration_ = 0.0f;	//��������������
	stateUpdate_ = std::bind(&PlayerBase::UpdateJump, this);
}

void PlayerBase::ChengeStateRoal(void)
{
	stateUpdate_ = std::bind(&PlayerBase::UpdateRoal, this);
}

void PlayerBase::ChengeStateDrop(void)
{
	SoundManager::GetInstance().Play(SoundManager::SRC::HIPDROP_SE, Sound::TIMES::ONCE);
	stateUpdate_ = std::bind(&PlayerBase::UpdateDrop, this);
}

void PlayerBase::ChengeStateDamage(void)
{
	MV1SetDifColorScale(modelId_, { 1.0f, 0.0f, 0.0f, 1.0f });//�_���[�W���͐Ԃ�����
	stateUpdate_ = std::bind(&PlayerBase::UpdateDamage, this);
}

void PlayerBase::ChengeStateDeath(void)
{
	stateUpdate_ = std::bind(&PlayerBase::UpdateDeath, this);
}

void PlayerBase::MakeWave(Wave::SPEED_TYPE speedType)
{
	std::shared_ptr<Wave> wave;
	wave = std::make_shared<Wave>(initPos_, speedType, color_);
	waves.push_back(wave);
}
