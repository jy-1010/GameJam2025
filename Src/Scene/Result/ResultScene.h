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
	//アニメーション種別
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

	// 読み込み
	void Load(void)override;
	// 初期化処理
	void Init(void)override;
	// 更新ステップ
	void Update(void)override;
	// 描画処理
	void Draw(void)override;
	// 解放処理
	void Release(void)override;
private:
	std::vector<int>models_;
	std::map<int, AnimationController*>anime_;
};

