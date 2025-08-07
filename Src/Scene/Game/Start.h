#pragma once

#include"../SceneBase.h"

class Start : public SceneBase
{
public:
	static constexpr int COUNT_START = 3;
	static constexpr int COUNT_INTERVAL = 60;

	Start();
	~Start()override;

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
	int countDownImg_[4];
	float cou_;

	int countDown_;
	int countInterval_;
};

