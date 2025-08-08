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

// コンストラクタ
SceneManager::SceneManager(void)
{
	sceneId_ = SCENE_ID::NONE;
	isGameEnd_ = false;

	// デルタタイム
	deltaTime_ = 1.0f / 60.0f;
}

// デストラクタ
SceneManager::~SceneManager(void)
{
	
}

// 初期化
void SceneManager::Init(void)
{
	// ロード画面生成
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
	// 最初はタイトル画面から
	ChangeScene(std::make_shared<TitleScene>(TitleScene()));
}


// 更新
void SceneManager::Update(void)
{
	// シーンがなければ終了
	if (scenes_.empty()) { return; }

	// デルタタイム
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;

	KeyConfig::GetInstance().Update();

	// ロード中
	if (Loading::GetInstance()->IsLoading())
	{
		// ロード更新
		Loading::GetInstance()->Update();

		// ロードの更新が終了していたら
		if (Loading::GetInstance()->IsLoading() == false)
		{
			// ロード後の初期化
			scenes_.back()->Init();
		}
	}		
	// 通常の更新処理
	else
	{
		// 現在のシーンの更新
		scenes_.back()->Update();
	}
}

// 描画
void SceneManager::Draw(void)
{
	camera_->SetBeforeDraw();
	// ロード中ならロード画面を描画
	if (Loading::GetInstance()->IsLoading())
	{
		// ロードの描画
		Loading::GetInstance()->Draw();
	}
	// 通常の更新
	else
	{
		// 積まれているもの全てを描画する
		for (auto& scene : scenes_) 
		{
			scene->Draw();
		}
	}
}

// 解放
void SceneManager::Release(void)
{
	//全てのシーンの解放・削除
	for (auto& scene : scenes_)
	{
		scene->Release();
	}
	scenes_.clear();

	// ロード画面の削除
	Loading::GetInstance()->Release();
	Loading::GetInstance()->DeleteInstance();
}

// 状態遷移関数
void SceneManager::ChangeScene(std::shared_ptr<SceneBase>scene)
{	
	// シーンが空か？
	if (scenes_.empty()) 
	{
		//空なので新しく入れる
		scenes_.push_back(scene);
	}
	else 
	{
		//末尾のものを新しい物に入れ替える
		scenes_.back() = scene;
	}

	ResetDeltaTime();

	// 読み込み(非同期)
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
	//新しく積むのでもともと入っている奴はまだ削除されない
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
	//積んであるものを消して、もともとあったものを末尾にする
	if (scenes_.size() > 1) 
	{
		scenes_.back()->Release();
		scenes_.pop_back();
	}
}

void SceneManager::JumpScene(std::shared_ptr<SceneBase> scene)
{
	// 全て解放
	scenes_.clear();

	// 新しく積む
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