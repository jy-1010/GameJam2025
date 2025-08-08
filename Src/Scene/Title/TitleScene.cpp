#include"TitleScene.h"

#include<DxLib.h>
#include"../../Application.h"
#include"../SceneManager/SceneManager.h"
#include"../../Manager/Input/KeyConfig.h"
#include"../../Manager/Resource/SoundManager.h"
#include"../../Manager/Camera/Camera.h"


TitleScene::TitleScene()
{
	SoundManager::GetInstance().Play(SoundManager::SRC::TITLE_BGM, Sound::TIMES::LOOP);
}

TitleScene::~TitleScene()
{
	SoundManager::GetInstance().Stop(SoundManager::SRC::TITLE_BGM);
}

void TitleScene::Load(void)
{

}
void TitleScene::Init(void)
{
	title_Img = LoadGraph("Data/Image/Title.png");
	con_Img = LoadGraph("Data/Image/co.png");

	modeId_ = MODE::PLAY;

	


}
void TitleScene::Update(void)
{
	
	auto& keyCon = KeyConfig::GetInstance();
	if(keyCon.IsTrgDown(KeyConfig::CONTROL_TYPE::SERECT_RIFHT,KeyConfig::JOYPAD_NO::PAD1))
	{
		switch (modeId_)
		{
		case MODE::PLAY:        modeId_ = MODE::OPERATION; break;
		case MODE::OPERATION:  modeId_ = MODE::EXIT; break;
		case MODE::EXIT:       modeId_ = MODE::PLAY; break;
		}
	}
	if (keyCon.IsTrgDown(KeyConfig::CONTROL_TYPE::SERECT_LEFT, KeyConfig::JOYPAD_NO::PAD1))
	{
		switch (modeId_)
		{
		case MODE::PLAY:        modeId_ = MODE::EXIT; break;
		case MODE::OPERATION:  modeId_ = MODE::PLAY; break;
		case MODE::EXIT:       modeId_ = MODE::OPERATION; break;
		}
	}
	

	switch (modeId_)
	{
	case TitleScene::MODE::PLAY:
		
		if (keyCon.IsTrgDown(KeyConfig::CONTROL_TYPE::DECISION, KeyConfig::JOYPAD_NO::PAD1))
		{
			SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME);
		}
		
	case TitleScene::MODE::EXIT:
		if (keyCon.IsTrgDown(KeyConfig::CONTROL_TYPE::END , KeyConfig::JOYPAD_NO::PAD1))
		{
			Application::GetInstance().End();
		}
		break;
	case TitleScene::MODE::OPERATION:

		
		DrawGraph(0, 0, con_Img, true);


		break;
	default:
		break;
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
		
		DrawGraph(Application::SCREEN_SIZE_X / 2 -400, Application::SCREEN_SIZE_Y / 2 -200, con_Img, true);


		
		break;
	default:
		break;
	}
}
void TitleScene::Release(void)
{

	DeleteGraph(title_Img);
}