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
	static constexpr int RANDAM_MAX = 100;	//�����̍ő�l(0~RAND_MAX�܂ł̒l�𐶐�����)

	static constexpr float JUMP_RATE = 0.03f;	//�W�����v�̔�����(0.0f~1.0f)
	static constexpr float DROP_RATE = 0.03f;	//�����̔�����(0.0f~1.0f)

	virtual void UpdateLand(void)override;
	virtual void UpdateJump(void)override;
};

