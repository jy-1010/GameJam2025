#pragma once
#include"../SceneBase.h"

class TitleScene : public SceneBase
{
public:

	enum class MODE	//タイトル遷移選択
	{
		PLAY,			//ゲームへ
		EXIT,			//終わる
		OPERATION,		//操作説明
	};	


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

	//タイトル画像ハンドル
	int title_Img;

	int con_Img;
	
	// シーンID
	MODE modeId_;

	bool gameExit_;

	bool drawAlive_;

};