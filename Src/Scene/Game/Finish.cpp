#include"Finish.h"

#include<DxLib.h>

#include"../../Application.h"
#include"../SceneManager/SceneManager.h"
#include"../../Utility/Utility.h"

Finish::Finish()
{
}

Finish::~Finish()
{
}

void Finish::Load(void)
{
	Utility::LoadImg(img_, "Data/Image/Finish.png");
}

void Finish::Init(void)
{
	scale_ = 0.0f;
}

void Finish::Update(void)
{
	scale_ += 0.05f;
	if (scale_ >= 1.0f) {
		SceneManager::GetInstance().JumpScene(SCENE_ID::RESULT);
	}
}

void Finish::Draw(void)
{
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, scale_, 0, img_, true);
}

void Finish::Release(void)
{
	DeleteGraph(img_);
}