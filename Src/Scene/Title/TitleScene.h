#pragma once
#include"../SceneBase.h"
#include <memory>;
#include"../../Object/Stage/Stage.h"
class Wave;

class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene()override;

	// 読み込み
	void Load(void)override;
	// 初期化処理
	void Init(void)override;
	// 更新ステップ
	void Update(void)override;
	// 描画処理
	void Draw(void)override;
	// 解放処理
	void Release(void)override;

private:
	std::shared_ptr<Wave> wave_;
	std::shared_ptr<Stage>stage_;
};