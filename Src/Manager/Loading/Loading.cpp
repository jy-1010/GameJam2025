#include "Loading.h"

#include <DxLib.h>

#include"../../Application.h"
#include"../../Utility/Utility.h"

Loading* Loading::instance_ = nullptr;

// �R���X�g���N�^
Loading::Loading()
	: handle_()
	, posX_(0)
	, posY_(0)
	, isLoading_(false)
	, loadTimer_(0)
	, animInterval_()
	, animCounter_()
{}

// �f�X�g���N�^
Loading::~Loading()
{}

// ������
void Loading::Init(void)
{
	loadTimer_ = 0;
	isLoading_ = false;
	posX_ = Application::SCREEN_SIZE_X / 2;
	posY_ = Application::SCREEN_SIZE_Y / 2;

	animCounter_ = 0;
	animInterval_ = 0;
}

// �ǂݍ���
void Loading::Load(void)
{
	// ���[�h���ɑg�ݍ��މ摜������΂����œǂݍ���

}

// �X�V
void Loading::Update(void)
{
	loadTimer_++;

	// �Ǎ����̂��̂��Ȃ��Ȃ����� or �ŒჍ�[�h���Ԍo��
	if (GetASyncLoadNum() == 0 && loadTimer_ >= MIN_LOAD_TIME)
	{
		// ���[�h�I��
		Init();
	}
	// �ǂݍ��ݒ�
	else
	{
		// ���[�h��ʂ𓮍삳����Ȃ炱���ɋL�q

	}
}

// �`��
void Loading::Draw(void)
{
	DrawRotaGraph(
		posX_, posY_,				// ���W
		1.0f,						// �g��l
		0.0f,						// ��]�l
		handle_[animCounter_],		// �n���h��
		true						// ���߃t���O
	);
}

// ���
void Loading::Release(void)
{
	for (auto& id : handle_) { DeleteGraph(id); }
}

// �񓯊��ǂݍ��݂ɐ؂�ւ���
void Loading::StartAsyncLoad(void)
{
	isLoading_ = true;
	// �񓯊��ǂݍ��݊J�n
	SetUseASyncLoadFlag(true);
}

// �����ǂݍ��݂ɐ؂�ւ���
void Loading::EndAsyncLoad(void)
{
	// �񓯊��ǂݍ��ݏI��
	SetUseASyncLoadFlag(false);
}
