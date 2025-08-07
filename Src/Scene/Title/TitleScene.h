#pragma once
#include"../SceneBase.h"

class TitleScene : public SceneBase
{
public:

	enum class MODE	//�^�C�g���J�ڑI��
	{
		PLAY,			//�Q�[����
		EXIT,			//�I���
		OPERATION,		//�������
	};	


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

	//�^�C�g���摜�n���h��
	int title_Img;

	int con_Img;
	
	// �V�[��ID
	MODE modeId_;

	bool gameExit_;

	bool drawAlive_;

};