#include"Select.h"
#include<DxLib.h>
#include"../../Application.h"
#include"../SceneManager/SceneManager.h"
#include"../../Manager/Input/KeyConfig.h"

#include "GameScene.h"

#include<DxLib.h>
#include"../../Utility/Utility.h"
Select::Select()
{
}

Select::~Select()
{
}

void Select::Load(void)
{
	img_[0] = Utility::LoadImg("Data/Image/Start/1.png");
	img_[1] = Utility::LoadImg("Data/Image/Start/2.png");
	img_[2] = Utility::LoadImg("Data/Image/Start/3.png");
	img_[3] = Utility::LoadImg("Data/Image/Start/4.png");
}
void Select::Init(void)
{
	selectNum_ = 1;

}
void Select::Update(void)
{
	auto& keyCon = KeyConfig::GetInstance();
	if (keyCon.IsTrgDown(KeyConfig::CONTROL_TYPE::SERECT_LEFT, KeyConfig::JOYPAD_NO::PAD1)) {
		if (selectNum_ > 1) {
			selectNum_--;
		}
	}

	if (keyCon.IsTrgDown(KeyConfig::CONTROL_TYPE::SERECT_RIFHT, KeyConfig::JOYPAD_NO::PAD1)) {
		if (selectNum_ < 4) {
			selectNum_++;
		}
	}

	if (keyCon.IsTrgDown(KeyConfig::CONTROL_TYPE::DECISION, KeyConfig::JOYPAD_NO::PAD1))
	{
		for (auto& scene : SceneManager::GetInstance().GetScenes())
		{
			std::shared_ptr<GameScene>game = std::dynamic_pointer_cast<GameScene>(scene);
			if (game == nullptr)
			{
				continue;
			}
			game->PlayerLoad(selectNum_);
		}
		SceneManager::GetInstance().PopScene();
	}

}
void Select::Draw(void)
{
	int xx = Application::SCREEN_SIZE_X;
	int yy = Application::SCREEN_SIZE_Y;
	int x = xx / 2;
	int y = yy / 2;
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(x / 2, y / 2, x + (x / 2), y + (y / 2), 0xffffff, true);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetFontSize(40);
	DrawString(x - 40 * 2, y - (y / 2), "êlêîëIë", 0x000000);
	SetFontSize(16);

	DrawRotaGraph(x, y, 1, 0, backImg_, true);
	DrawRotaGraph(x, y, 1, 0, img_[selectNum_-1], true);
}
void Select::Release(void)
{
	for (auto& id : img_) { DeleteGraph(id); }
	DeleteGraph(backImg_);
}
