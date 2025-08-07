#include"Start.h"

#include<string>

#include"../../Utility/Utility.h"
#include"../../Application.h"
#include"../SceneManager/SceneManager.h"

#include"Explanat.h"

Start::Start():
	countDownImg_(),
	cou_(),
	countDown_(),
	countInterval_()
{
}

Start::~Start()
{
}

void Start::Load(void)
{
	for (int i = 0; i < 4; i++) {
		countDownImg_[i] = Utility::LoadImg("Data/Image/Start/" + std::to_string(i) + ".png");
	}
}

void Start::Init(void)
{
	countDown_ = COUNT_START;
	countInterval_ = 0;
	cou_ = 0.0f;

	SceneManager::GetInstance().PushScene(std::make_shared<Explanat>());
}

void Start::Update(void)
{
	cou_ += 0.1f;
	if (countDown_ > 0) {
		if (++countInterval_ >= COUNT_INTERVAL) {
			countInterval_ = 0;
			countDown_--;
		}
	}
	else {
		if (++countInterval_ >= COUNT_INTERVAL / 2) {
			SceneManager::GetInstance().PopScene();
		}
	}
}

void Start::Draw(void)
{
	int xx = Application::SCREEN_SIZE_X;
	int yy = Application::SCREEN_SIZE_Y;
	int x = xx / 2;
	int y = yy / 2;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, xx, yy, 0x0f0f0f, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawRotaGraph(x, y, abs(sinf(cou_)) + 0.5, 0, countDownImg_[countDown_], true);
}

void Start::Release(void)
{
	for (auto& img : countDownImg_) { DeleteGraph(img); }
}