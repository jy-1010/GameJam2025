#pragma once
#include"../SceneBase.h"
#include <memory>;
#include"../../Object/Stage/Stage.h"
class Wave;

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
	std::shared_ptr<Wave> wave_;
	std::shared_ptr<Stage>stage_;

	//�^�C�g���摜�n���h��
	int title_Img;
	
	// �V�[��ID
	MODE modeId_;


	bool isRightKeyAlive ;

};