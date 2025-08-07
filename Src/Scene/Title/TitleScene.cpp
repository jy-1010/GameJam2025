#include"TitleScene.h"
#include "../../Object/Wave.h"
#include<DxLib.h>

#include"../SceneManager/SceneManager.h"


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Load(void)
{
}
void TitleScene::Init(void)
{
	wave_ = std::make_shared<Wave>(VECTOR(), Wave::SPEED_TYPE::FAST, 0xff00ff);
}
void TitleScene::Update(void)
{
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME);
	}
	wave_->Update();
	if (CheckHitKey(KEY_INPUT_R))
	{
		wave_->Reset();
	}
}
void TitleScene::Draw(void)
{
	wave_->Draw();
	DrawString(0, 0, "タイトルシーン", 0xffffff);
}
void TitleScene::Release(void)
{
}