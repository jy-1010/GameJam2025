#pragma once
#include "PlayerBase.h"
class CPU :
    public PlayerBase
{
public:
	CPU(GameScene& gameScene, int playerNum, VECTOR pos);
	~CPU(void)override;

	virtual void Damage(VECTOR vec)override;
private:
	static constexpr int RANDAM_MAX = 100;	//乱数の最大値(0~RAND_MAXまでの値を生成する)

	static constexpr float JUMP_RATE = 0.03f;	//ジャンプの発生率(0.0f~1.0f)
	static constexpr float DROP_RATE = 0.03f;	//落下の発生率(0.0f~1.0f)

	virtual void UpdateLand(void)override;
	virtual void UpdateJump(void)override;
};

