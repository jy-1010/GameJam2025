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
	con_Img = LoadGraph("Data/Image/Title_use.png");
	play_Img = LoadGraph("Data/Image/Play.png");
	eixt_Img = LoadGraph("Data/Image/Exit.png");

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

		break;
	case TitleScene::MODE::EXIT:
		IsEnd_ = true;

		if (IsEnd_ == true)
		{
			if(keyCon.IsTrgDown(KeyConfig::CONTROL_TYPE::EXITDECISION, KeyConfig::JOYPAD_NO::PAD1))
			{
				Application::GetInstance().End();
			}
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
		DrawExtendGraph(550, Application::SCREEN_SIZE_Y / 2+200 , 950, 1000, play_Img, true);
		
		break;
	case TitleScene::MODE::EXIT:
		DrawString(0, 0, "タイトルへ", 0xffffff); 
		DrawExtendGraph(600, Application::SCREEN_SIZE_Y / 2+200, 900, 1000, eixt_Img, true);

		break;
	case TitleScene::MODE::OPERATION:
		DrawString(0, 0, "説明へ", 0xffffff);
		
		//DrawGraph(Application::SCREEN_SIZE_X / 2 -400, Application::SCREEN_SIZE_Y / 2 -200, con_Img, true);
		DrawExtendGraph(Application::SCREEN_SIZE_X / 2 - 500, Application::SCREEN_SIZE_Y / 2 - 200, 1250, 900, con_Img, true);

		
		break;
	default:
		break;
	}
}
void TitleScene::Release(void)
{

	DeleteGraph(title_Img);
	DeleteGraph(con_Img);
}