#pragma once
#include"../SceneBase.h"

class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene()override;

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

};