#include "ResultScene.h"

#include<string>

#include"../../Utility/Utility.h"
#include"../../Application.h"
#include"../SceneManager/SceneManager.h";
#include"../../Manager/Resource/SoundManager.h";
#include"../../Manager/Camera/Camera.h"

ResultScene::ResultScene()
{
	SoundManager::GetInstance().Play(SoundManager::SRC::RESULT_BGM, Sound::TIMES::LOOP);
}

ResultScene::~ResultScene()
{
	SoundManager::GetInstance().Stop(SoundManager::SRC::RESULT_BGM);
}

void ResultScene::Load(void)
{
	SceneManager::GetInstance().GetCamera().lock()->SetPos(VAdd(RESULT_POS[0], C_POS));
	SceneManager::GetInstance().GetCamera().lock()->SetTargetPos(VAdd(RESULT_POS[0], T_POS));

	Utility::LoadImg(img_, "Data/Image/VICTORY.png");
	for (int i = 1; i <= SceneManager::GetInstance().GetTopNum(); i++) {
		models_.emplace_back(MV1LoadModel((MODEL_ID + std::to_string(SceneManager::GetInstance().GetLanking(i)) + ".mv1").c_str()));
		anime_[models_[models_.size() - 1]] = new AnimationController(models_[models_.size() - 1]);
		MV1SetPosition(models_[models_.size() - 1], RESULT_POS[models_.size() - 1]);
		for (int i = 0; i < (int)ANIM_TYPE::MAX; i++) {
			anime_[models_[models_.size() - 1]]->AddInFbx(i, 30.0f, i);
		}
		anime_[models_[models_.size() - 1]]->Add((int)ANIM_TYPE::DANCE1, 30.0f, "Data/Model/Player/Dance1.mv1");

		anime_[models_[models_.size() - 1]]->Play((int)ANIM_TYPE::DANCE1);
	}
}

void ResultScene::Init(void)
{
	nowTrg_ = (CheckHitKeyAll() == 1) ? true : false;
	prevTrg_ = nowTrg_;
	nowTrg_ = (CheckHitKeyAll() == 1) ? true : false;
}

void ResultScene::Update(void)
{
	for (auto& a : anime_) { a.second->Update(); }

	prevTrg_ = nowTrg_;
	nowTrg_ = (CheckHitKey(KEY_INPUT_SPACE)==0) ?false : true;

	if (!prevTrg_ && nowTrg_) {
		SceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
	}
}

void ResultScene::Draw(void)
{
	int x = Application::SCREEN_SIZE_X;
	int y = Application::SCREEN_SIZE_Y;
	DrawExtendGraph(0, 0, x, y, img_, true);

	for (auto& model : models_) {
		MV1DrawModel(model);
	}
}

void ResultScene::Release(void)
{
	for (auto& a : anime_) { a.second->Release(); delete a.second; }
	for (auto& model : models_) { MV1DeleteModel(model); }
	models_.clear();
	DeleteGraph(img_);
}
