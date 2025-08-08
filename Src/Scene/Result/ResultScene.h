#pragma once
#include<DxLib.h>
#include<vector>
#include<map>
#include "../SceneBase.h"
#include"../../Manager/AnimationController/AnimationController.h"
class ResultScene :
    public SceneBase
{
public:
	static constexpr const char* MODEL_ID = "Data/Model/Player/Player";
	static constexpr VECTOR RESULT_POS[4] =
	{
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f}
	};
	//�A�j���[�V�������
	enum class ANIM_TYPE
	{
		DEATH,
		DUCK,
		HIT_REACT,
		IDLE,
		IDLE_ATTACK,
		IDLE_HOLD,
		JUMP,
		JUMP_IDLE,
		JUMP_LAND,
		NO,
		PUNCH,
		RUN,
		RUN_ATTACK,
		RUN_HOLD,
		WALK,
		WALK_HOLD,
		WAVE,
		YES,
		MAX,
		DANCE1,
	};

	ResultScene();
	~ResultScene()override;

	// �ǂݍ���
	void Load(void)override;
	// ����������
	void Init(void)override;
	// �X�V�X�e�b�v
	void Update(void)override;
	// �`�揈��
	void Draw(void)override;
	// �������
	void Release(void)override;
private:
	std::vector<int>models_;
	std::map<int, AnimationController*>anime_;
};

