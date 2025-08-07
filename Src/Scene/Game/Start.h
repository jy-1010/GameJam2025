#pragma once

#include"../SceneBase.h"

class Start : public SceneBase
{
public:
	static constexpr int COUNT_START = 3;
	static constexpr int COUNT_INTERVAL = 60;

	Start();
	~Start()override;

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
	int countDownImg_[4];
	float cou_;

	int countDown_;
	int countInterval_;
};

