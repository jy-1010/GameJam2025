#include "SceneManager.h"

#include <DxLib.h>

#include "../../Manager/Loading/Loading.h"

#include"../Title/TitleScene.h"
#include"../Game/GameScene.h"

SceneManager* SceneManager::instance_ = nullptr;

// �R���X�g���N�^
SceneManager::SceneManager(void)
{
	sceneId_ = SCENE_ID::NONE;
	isGameEnd_ = false;
}

// �f�X�g���N�^
SceneManager::~SceneManager(void)
{
}

// ������
void SceneManager::Init(void)
{
	// ���[�h��ʐ���
	Loading::GetInstance()->CreateInstance();
	Loading::GetInstance()->Init();
	Loading::GetInstance()->Load();


	// �ŏ��̓^�C�g����ʂ���
	ChangeScene(std::make_shared<TitleScene>(TitleScene()));
}


// �X�V
void SceneManager::Update(void)
{
	// �V�[�����Ȃ���ΏI��
	if (scenes_.empty()) { return; }

	// ���[�h��
	if (Loading::GetInstance()->IsLoading())
	{
		// ���[�h�X�V
		Loading::GetInstance()->Update();

		// ���[�h�̍X�V���I�����Ă�����
		if (Loading::GetInstance()->IsLoading() == false)
		{
			// ���[�h��̏�����
			scenes_.back()->Init();
		}
	}		
	// �ʏ�̍X�V����
	else
	{
		// ���݂̃V�[���̍X�V
		scenes_.back()->Update();
	}
}

// �`��
void SceneManager::Draw(void)
{
	// ���[�h���Ȃ烍�[�h��ʂ�`��
	if (Loading::GetInstance()->IsLoading())
	{
		// ���[�h�̕`��
		Loading::GetInstance()->Draw();
	}
	// �ʏ�̍X�V
	else
	{
		// �ς܂�Ă�����̑S�Ă�`�悷��
		for (auto& scene : scenes_) 
		{
			scene->Draw();
		}
	}
}

// ���
void SceneManager::Release(void)
{
	//�S�ẴV�[���̉���E�폜
	for (auto& scene : scenes_)
	{
		scene->Release();
	}
	scenes_.clear();

	// ���[�h��ʂ̍폜
	Loading::GetInstance()->Release();
	Loading::GetInstance()->DeleteInstance();
}

// ��ԑJ�ڊ֐�
void SceneManager::ChangeScene(std::shared_ptr<SceneBase>scene)
{	
	// �V�[�����󂩁H
	if (scenes_.empty()) 
	{
		//��Ȃ̂ŐV���������
		scenes_.push_back(scene);
	}
	else 
	{
		//�����̂��̂�V�������ɓ���ւ���
		scenes_.back() = scene;
	}

	// �ǂݍ���(�񓯊�)
	Loading::GetInstance()->StartAsyncLoad();
	scenes_.back()->Load();
	Loading::GetInstance()->EndAsyncLoad();
}

void SceneManager::ChangeScene(SCENE_ID scene)
{
	switch (scene)
	{
	case SceneManager::SCENE_ID::TITLE:
		ChangeScene(std::make_shared<TitleScene>());
		break;
	case SceneManager::SCENE_ID::GAME:
		ChangeScene(std::make_shared<GameScene>());
		break;
	default:
		break;
	}
}

void SceneManager::PushScene(std::shared_ptr<SceneBase> scene)
{
	//�V�����ςނ̂ł��Ƃ��Ɠ����Ă���z�͂܂��폜����Ȃ�
	scenes_.push_back(scene);
}

void SceneManager::PushScene(SCENE_ID scene)
{
	switch (scene)
	{
	case SceneManager::SCENE_ID::TITLE:
		PushScene(std::make_shared<TitleScene>());
		break;
	case SceneManager::SCENE_ID::GAME:
		PushScene(std::make_shared<GameScene>());
		break;
	default:
		break;
	}
}

void SceneManager::PopScene(void)
{
	//�ς�ł�����̂������āA���Ƃ��Ƃ��������̂𖖔��ɂ���
	if (scenes_.size() > 1) 
	{
		scenes_.pop_back();
	}
}

void SceneManager::JumpScene(std::shared_ptr<SceneBase> scene)
{
	// �S�ĉ��
	scenes_.clear();

	// �V�����ς�
	scenes_.push_back(scene);
}

void SceneManager::JumpScene(SCENE_ID scene)
{
	switch (scene)
	{
	case SceneManager::SCENE_ID::TITLE:
		JumpScene(std::make_shared<TitleScene>());
		break;
	case SceneManager::SCENE_ID::GAME:
		JumpScene(std::make_shared<GameScene>());
		break;
	default:
		break;
	}
}
