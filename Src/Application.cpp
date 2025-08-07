#include "Application.h"

#include <DxLib.h>

#include"Manager/FPS/FPS.h"
#include"Scene/SceneManager/SceneManager.h"

Application* Application::instance_ = nullptr;

// �R���X�g���N�^
Application::Application(void)
{
	isInitFail_ = false;
	isReleaseFail_ = false;
	fps_ = nullptr;
}

// �f�X�g���N�^
Application::~Application(void)
{
}

// ������
void Application::Init(void)
{
	// �A�v���P�[�V�����̏����ݒ�
	SetWindowText("�x�[�X");

	// �E�B���h�E�֘A
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);	// �T�C�Y�ύX
	ChangeWindowMode(true);	// false = �t���X�N���[��

	// DxLib�̏�����
	isInitFail_ = false;
	if (DxLib_Init() == -1)
	{
		// ���������s
		isInitFail_ = true;
		return;
	}

	// �`����ʂ𗠂ɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// �L�[���䏉����
	SetUseDirectInputFlag(true);



	// �V�[���Ǘ�������
	SceneManager::CreateInstance();
	SceneManager::GetInstance().Init();

	// FPS������
	fps_ = new FPS;
	fps_->Init();
}

// �Q�[�����[�v
void Application::Run(void)
{
	// �Q�[�����[�v
	while (ProcessMessage() == 0)
	{
		// �t���[�����[�g�X�V
		// 1/60�b�o�߂��Ă��Ȃ��Ȃ�ă��[�v������
		if (!fps_->UpdateFrameRate()) continue;

		SceneManager::GetInstance().Update();	// �V�[���Ǘ��X�V
		fps_->CalcFrameRate();					// �t���[�����[�g�v�Z

		ClearDrawScreen();

		SceneManager::GetInstance().Draw();		// �V�[���Ǘ��`��
		fps_->DrawFrameRate();					// �t���[�����[�g�`��

		ScreenFlip();
	}
}

// ���
void Application::Release(void)
{
	// �V�[���Ǘ�����E�폜	
	SceneManager::GetInstance().Release();
	SceneManager::DeleteInstance();

	// �t���[�����[�g���
	delete fps_;

	// DxLib�I��
	if (DxLib_End() == -1)
	{
		isReleaseFail_ = true;
	}
}
