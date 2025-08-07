#include"TitleScene.h"
#include "../../Object/Wave.h"
#include<DxLib.h>
#include"../../Application.h"
#include"../SceneManager/SceneManager.h"
#include"../../Manager/Camera/Camera.h"
#include"../../Manager/Input/InputManager.h"


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Load(void)
{
	stage_ = std::make_shared<Stage>();
	stage_->Load();
	SceneManager::GetInstance().GetCamera().lock()->SetPos(Stage::C_POS);
	SceneManager::GetInstance().GetCamera().lock()->SetTargetPos(stage_->GetCenter());
}
void TitleScene::Init(void)
{
	title_Img = LoadGraph("Data/Image/Title.png");

	modeId_ = MODE::PLAY;

	


}
void TitleScene::Update(void)
{
	
	
	if(CheckHitKey(KEY_INPUT_RIGHT))
	{
		switch (modeId_)
		{
		case MODE::PLAY:        modeId_ = MODE::OPERATION; break;
		case MODE::OPERATION:  modeId_ = MODE::EXIT; break;
		case MODE::EXIT:       modeId_ = MODE::PLAY; break;
		}
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		switch (modeId_)
		{
		case MODE::PLAY:        modeId_ = MODE::EXIT; break;
		case MODE::OPERATION:  modeId_ = MODE::PLAY; break;
		case MODE::EXIT:       modeId_ = MODE::OPERATION; break;
		}
	}
	

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME);
	}
	
	

	

}
void TitleScene::Draw(void)
{

	
	DrawGraph(0, 0, title_Img, true);

	switch (modeId_)
	{
	case TitleScene::MODE::PLAY:
		DrawString(0, 0, "ゲームシーン", 0xffffff);
		break;
	case TitleScene::MODE::EXIT:
		DrawString(0, 0, "タイトルへ", 0xffffff);
		break;
	case TitleScene::MODE::OPERATION:
		DrawString(0, 0, "説明へ", 0xffffff);
		break;
	default:
		break;
	}
	stage_->Draw();

	wave_->Draw();
	DrawString(0, 0, "タイトルシーン", 0xffffff);
}
void TitleScene::Release(void)
{
	stage_->Release();

	DeleteGraph(title_Img);
}