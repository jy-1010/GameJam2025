#include <DxLib.h>
#include "../../Application.h"
#include "../../Manager/Resource/ResourceManager.h"
#include "../../Utility/Utility.h"
#include "../../Object/Player/PlayerBase.h"
#include "LifeUI.h"

LifeUI::LifeUI(int playerNum)
{
	playerNum_ = playerNum;	//プレイヤー番号を設定
	pos_.x = playerNum_ % 2 == 0 ? MARGIN  : Application::SCREEN_SIZE_X - MARGIN - LIFE_ICON_SUM_SIZE_X ;	//表示位置を設定
	pos_.y = playerNum_ < 2 ? Application::SCREEN_SIZE_Y - MARGIN  - LIFE_ICON_SUM_SIZE_Y: MARGIN ;	//表示位置を設定
	auto& resMana = ResourceManager::GetInstance();
	buttonImageId_ = playerNum_ == 0 ? resMana.Load(ResourceManager::SRC::RED_BUTTON).handleId_ :
		playerNum_ == 1 ? resMana.Load(ResourceManager::SRC::BLUE_BUTTON).handleId_ :
		playerNum_ == 2 ? resMana.Load(ResourceManager::SRC::YELLOW_BUTTON).handleId_ :
		resMana.Load(ResourceManager::SRC::GREEN_BUTTON).handleId_;	//ボタンの画像IDを設定
	graybuttonImageId_ = resMana.Load(ResourceManager::SRC::GRAY_BUTTON).handleId_;	//グレーのボタンの画像IDを設定
}

LifeUI::~LifeUI(void)
{
}

void LifeUI::Init(void)
{
}

void LifeUI::Draw(void)
{
	int x = pos_.x +LIFE_ICON_INTERVAL;	//表示位置のX座標
	int topY = pos_.y + LIFE_ICON_INTERVAL;	//表示位置のY座標
	int downY = pos_.y + LIFE_ICON_INTERVAL + static_cast<int>(LIFE_ICON_RADIUS *2);	//表示位置のY座標
	for (int i = 0; i < PlayerBase::MAX_HP;i++)
	{
		DrawExtendGraph(x, topY, x + LIFE_ICON_RADIUS * 2, downY, i < life_ ?buttonImageId_ : graybuttonImageId_,true);	//ライフアイコンを描画
		x += LIFE_ICON_RADIUS * 2 + LIFE_ICON_INTERVAL;	//次のアイコンのX座標を計算
	}
	
}

void LifeUI::SetLife(int life)
{
	life_ = life;
}
