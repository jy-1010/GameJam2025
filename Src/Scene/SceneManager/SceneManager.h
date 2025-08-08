#pragma once

#include<memory>
#include<list>

#include <chrono>

#include "../Game/GameScene.h"

class SceneBase;
class Camera;

class SceneManager
{
public:
	// シーン管理用
	enum class SCENE_ID
	{
		NONE = -1,

		TITLE,
		GAME,
		RESULT,

		MAX
	};

	// シングルトン（生成・取得・削除）
	static void CreateInstance(void) { if (instance_ == nullptr) { instance_ = new SceneManager(); } };
	static SceneManager& GetInstance(void) { return *instance_; };
	static void DeleteInstance(void) { if (instance_ != nullptr) { delete instance_; instance_ = nullptr; } }

	void Init(void);	// 初期化
	void Update(void);	// 更新
	void Draw(void);	// 描画
	void Release(void);	// 解放

	// 状態遷移
	void ChangeScene(std::shared_ptr<SceneBase>scene);
	void ChangeScene(SCENE_ID scene);

	// シーンを新しく積む
	void PushScene(std::shared_ptr<SceneBase>scene);
	void PushScene(SCENE_ID scene);

	// 最後に追加したシーンを削除する。
	void PopScene(void);

	// 強制的に特定のシーンに飛ぶ。リセットをかけ特定のシーンのみにする。
	void JumpScene(std::shared_ptr<SceneBase>scene);
	void JumpScene(SCENE_ID scene);

	// シーンIDの取得
	SCENE_ID GetSceneID(void) const { return sceneId_; };

	// ゲーム終了
	void GameEnd(void) { isGameEnd_ = true; }
	bool GetGameEnd(void) { return isGameEnd_; }

	// デルタタイムの取得
	float GetDeltaTime(void) const;
	void ResetDeltaTime(void);

	// ゲーム終了取得
	

	std::weak_ptr<Camera> GetCamera(void) { return camera_; }

	// ランキングの取得
	int GetLanking(int lankNum) const { return lanking_[lankNum - 1]; }
	// ランキングの設定
	void SetLanking(int lankNum, int playerNum) { lanking_[lankNum - 1] = playerNum + 1; }
	// ランキングの初期化
	void InitLanking(void) { for (int i = 0; i < GameScene::PLAYER_MAX; i++) { lanking_[i] = 0; } }
	// 1位が何人いるかの設定
	void SetTopNum(int num) { topNum_ = num; }
	int GetTopNum(void) { return topNum_; }


	std::list<std::shared_ptr<SceneBase>>GetScenes(void) { return scenes_; }

private:
	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	SceneManager(void);
	// デストラクタも同様
	~SceneManager(void);

	//// コピー・ムーブ操作を禁止
	//SceneManager(const SceneManager&) = delete;
	//SceneManager& operator=(const SceneManager&) = delete;
	//SceneManager(SceneManager&&) = delete;
	//SceneManager& operator=(SceneManager&&) = delete;

	// 下記をコンパイルエラーさせるため 上記を追加
	// SceneManager copy = *SceneManager::GetInstance();
	// SceneManager copied(*SceneManager::GetInstance());
	// SceneManager moved = std::move(*SceneManager::GetInstance());
	// 
	// 静的インスタンス
	static SceneManager* instance_;

	//Drawの関係上Backを最新のシーンとする
	//基本的には要素は一つだけだがポーズシーンなどが積み重なる形
	std::list<std::shared_ptr<SceneBase>>scenes_;

	// デルタタイム
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	// シーンID
	SCENE_ID sceneId_;

	// ゲーム終了
	bool isGameEnd_;

	std::shared_ptr<Camera> camera_;

	int lanking_[GameScene::PLAYER_MAX];
	int topNum_;

};

using SCENE_ID = SceneManager::SCENE_ID;