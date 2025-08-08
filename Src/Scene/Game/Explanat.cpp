#include"Explanat.h"

#include<DxLib.h>

#include"../../Utility/Utility.h"
#include"../../Application.h"
#include"../SceneManager/SceneManager.h"

#include"Select.h"

Explanat::Explanat():
	img_(-1),
	bottonImg_(),
	s_(0.0f)
{
}

Explanat::~Explanat()
{
}

void Explanat::Load(void)
{
	img_ = Utility::LoadImg("Data/Image/Start/Illustrate.png");
	bottonImg_[0] = Utility::LoadImg("Data/Image/Start/SpaceKey.png");
	bottonImg_[1] = Utility::LoadImg("Data/Image/Start/Abutton.png");
}

void Explanat::Init(void)
{
	s_ = 0.0f;
	prevTrg_ = true;
	nowTrg_ = true;
	SceneManager::GetInstance().PushScene(std::make_shared<Select>());
}

void Explanat::Update(void)
{
	int input = GetJoypadInputState(DX_INPUT_PAD1);
	prevTrg_ = nowTrg_;
	nowTrg_ = ((input & PAD_INPUT_A) == 0 && (CheckHitKey(KEY_INPUT_SPACE) == 0)) ? false : true;
	if (!prevTrg_ && nowTrg_) {
		SceneManager::GetInstance().PopScene();
	}

	s_ += 0.1f;
}

void Explanat::Draw(void)
{
	int xx = Application::SCREEN_SIZE_X;
	int yy = Application::SCREEN_SIZE_Y;
	int x = xx / 2;
	int y = yy / 2;

	DrawExtendGraph(x / 2, y / 2, x + (x / 2), y + (y / 2), img_, true);
	DrawRotaGraph(x, y, 1, 0, img_, true);
	DrawRotaGraph(x + (x / 2), y + (y / 2) - 30, abs(sinf(s_))*0.1f+0.3f, 0, bottonImg_[(IsAnyXboxController()) ? 1 : 0], true);
}

void Explanat::Release(void)
{
	for (auto& id : bottonImg_) { DeleteGraph(id); }

	DeleteGraph(img_);
}

bool Explanat::IsAnyXboxController()
{
	XINPUT_STATE state;
	for (int i = 0; i < 4; ++i) {
		if (GetJoypadXInputState(DX_INPUT_PAD1 + i, &state) == 0) { return true; }
	}
	return false;
}

