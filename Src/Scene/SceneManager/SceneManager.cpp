#include "SceneManager.h"

#include <DxLib.h>

#include "../../Manager/Loading/Loading.h"

#include"../Title/TitleScene.h"
#include"../Game/GameScene.h"
#include"../Game/Start.h"

#include "../../Manager/Camera/Camera.h"
#include "../../Manager/Resource/ResourceManager.h"
#include "../../Manager/Resource/SoundManager.h"

SceneManager* SceneManager::instance_ = nullptr;

// �R���X�g���N�^
SceneManager::SceneManager(void)
{
	sceneId_ = SCENE_ID::NONE;
	isGameEnd_ = false;

	// �f���^�^�C��
	deltaTime_ = 1.0f / 60.0f;
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

	camera_ = std::make_shared<Camera>();
	camera_->Init();
	camera_->SetPos({ 0.0f,10000.0f,50.0f });
	camera_->SetTargetPos({ 0.0f,0.0f,0.0f });

	KeyConfig::CreateInstance();

	ResourceManager::CreateInstance();
	SoundManager::CreateInstance();
	InitLanking();
	// �ŏ��̓^�C�g����ʂ���
	ChangeScene(std::make_shared<TitleScene>(TitleScene()));
}


// �X�V
void SceneManager::Update(void)
{
	// �V�[�����Ȃ���ΏI��
	if (scenes_.empty()) { return; }

	// �f���^�^�C��
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;

	KeyConfig::GetInstance().Update();

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
	camera_->SetBeforeDraw();
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

	ResetDeltaTime();

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

	Loading::GetInstance()->StartAsyncLoad();
	scenes_.back()->Load();
	Loading::GetInstance()->EndAsyncLoad();
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
		scenes_.back()->Release();
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

float SceneManager::GetDeltaTime(void) const
{
	return 1.0f / 60;
	//return deltaTime_;
}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();
}