#pragma once
#include "../../Common/Vector2.h"

class LifeUI
{
public:

	LifeUI(int playerNum);
	~LifeUI(void);
	void Init(void);
	void Draw(void);
	void SetLife(int life);

private:

	static constexpr int MARGIN = 30;	//余白の大きさ
	static constexpr float LIFE_ICON_RADIUS = 20.0f;	//ライフアイコンの大きさ
	static constexpr int LIFE_ICON_INTERVAL = 10;	//ライフアイコンの間隔
	static constexpr int LIFE_ICON_SUM_SIZE_X = 160;
	static constexpr int LIFE_ICON_SUM_SIZE_Y = 60;
	Vector2I pos_;	//表示位置(左上座標)
	int playerNum_;	//プレイヤー番号
	int life_;		//ライフ数
	int buttonImageId_;	//ボタンの画像ID
	int graybuttonImageId_;	//グレーのボタンの画像ID
};

