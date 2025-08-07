#pragma once
#include "../../Common/Vector2.h"

class LifeUI
{
public:

	LifeUI(int playerNum);
	~LifeUI(void);
	void Init(void);
	void Draw(void);
	void SetLife(int life);

private:

	static constexpr int MARGIN = 30;	//�]���̑傫��
	static constexpr float LIFE_ICON_RADIUS = 20.0f;	//���C�t�A�C�R���̑傫��
	static constexpr int LIFE_ICON_INTERVAL = 10;	//���C�t�A�C�R���̊Ԋu
	static constexpr int LIFE_ICON_SUM_SIZE_X = 160;
	static constexpr int LIFE_ICON_SUM_SIZE_Y = 60;
	Vector2I pos_;	//�\���ʒu(������W)
	int playerNum_;	//�v���C���[�ԍ�
	int life_;		//���C�t��
	int buttonImageId_;	//�{�^���̉摜ID
	int graybuttonImageId_;	//�O���[�̃{�^���̉摜ID
};

