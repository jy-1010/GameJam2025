#include"GameScene.h"

#include<DxLib.h>
#include<cmath>

#include"../../Utility/Utility.h"
#include"../../Application.h"
#include"../SceneManager/SceneManager.h"
#include"../../Manager/Camera/Camera.h"
#include"../../Manager/Resource/SoundManager.h"

#include"Start.h"
#include"../../Object/Stage/Stage.h"
//#include"../../Object/Player/PlayerBase.h"
#include"../../Object/Player/CPU.h"

#include "../../Utility/Utility.h"

int GameScene::hitStop_ = 0;

int GameScene::slow_ = 0;
int GameScene::slowInter_ = 0;

int GameScene::shake_ = 0;
ShakeKinds GameScene::shakeKinds_ = ShakeKinds::DIAG;
ShakeSize GameScene::shakeSize_ = ShakeSize::MEDIUM;

GameScene::GameScene():
	mainScreen_(-1),
	stage_(),
	timeImg_(-1),
	limitTime_(0.0f)
{
	SoundManager::GetInstance().Play(SoundManager::SRC::GAME_BGM, Sound::TIMES::LOOP);
}

GameScene::~GameScene()
{
	SoundManager::GetInstance().Stop(SoundManager::SRC::GAME_BGM);
}

void GameScene::Load(void)
{
	mainScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y);

	Utility::LoadImg(timeImg_, "Data/Image/Time.png");

	stage_ = std::make_shared<Stage>();
	stage_->Load();

	auto playerPoss = stage_->GetPos();

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (i == 0)
		{
			players_[i] = std::make_shared<PlayerBase>(*this,i, playerPoss[i]);
		}
		else
		{
			players_[i] = std::make_shared<CPU>(*this,i, playerPoss[i]);
		}
	}

	SceneManager::GetInstance().GetCamera().lock()->SetPos(Stage::C_POS);
	SceneManager::GetInstance().GetCamera().lock()->SetTargetPos(stage_->GetCenter());
}
void GameScene::Init(void)
{
	limitTime_ = (float)LIMIT_TIME;
	SceneManager::GetInstance().InitLanking();	// ランキングの初期化
	// ヒットストップカウンターの初期化
	hitStop_ = 0;

	// スローカウンターの初期化
	slow_ = 0;
	slowInter_ = 5;

	aliveCount_ = PLAYER_MAX;	// 生存しているプレイヤーの数を初期化

	// 画面揺れ関係の初期化-----------------------------------------------------------
	shake_ = 0;
	shakeKinds_ = ShakeKinds::DIAG;
	shakeSize_ = ShakeSize::MEDIUM;;
	//--------------------------------------------------------------------------------

	this->Update();
	SceneManager::GetInstance().PushScene(std::make_shared<Start>());
}
void GameScene::Update(void)
{
	if (hitStop_ > 0) { hitStop_--; return; }
	if (shake_ > 0) { shake_--; }
	if (slow_ > 0) {
		slow_--;
		if (slow_ % slowInter_ != 0) { return; }
	}
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (players_[i])
		{
			players_[i]->Update();
		}
	}
	ColisionWave();

	if (aliveCount_ <= 1)
	{	// 生存しているプレイヤーが1人以下なら
		if (aliveCount_ == 1)
		{
			// 生存しているプレイヤーが1人なら
			for (int i = 0; i < PLAYER_MAX; i++)
			{
				if (players_[i] && !players_[i]->IsDeath())
				{	// 生存しているプレイヤーを見つけたら
					SceneManager::GetInstance().SetLanking(aliveCount_, i);	// ランキングに登録
					break;
				}
			}
		}
		//リザルトへの遷移処理


		return;
	}

	limitTime_ -= SceneManager::GetInstance().GetDeltaTime();
	if (limitTime_ <= 0.0f) {
		// 時間切れ

	}
}
void GameScene::Draw(void)
{
	SetDrawScreen(mainScreen_);
	ClearDrawScreen();
	auto camera = SceneManager::GetInstance().GetCamera();
	camera.lock()->SetBeforeDraw();

	//描画処理-----------------------------------------
	using app = Application;
	int xx = app::SCREEN_SIZE_X;
	int yy = app::SCREEN_SIZE_Y;
	int x = xx / 2;
	int y = yy / 2;

	stage_->Draw();

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		players_[i]->Draw();
	}

	DrawRotaGraph(x, 70, 2, 0, timeImg_, true);
	SetFontSize(100);
	DrawFormatString(x - 130, 30, 0xffffff, "%.2f", limitTime_);
	SetFontSize(16);
	DrawString(0, 0, "ゲームシーン", 0xffffff);
	//-------------------------------------------------

	SetDrawScreen(DX_SCREEN_BACK);

	Vector2I s = ShakePoint();
	DrawGraph(s.x, s.y, mainScreen_, true);
}
void GameScene::Release(void)
{

	DeleteGraph(mainScreen_);
}

void GameScene::Shake(ShakeKinds kinds, ShakeSize size, int time)
{
	if ((abs(shake_ - time) > 10) || shake_ <= 0)shake_ = time;
	shakeKinds_ = kinds;
	shakeSize_ = size;
}

void GameScene::PlayerDeath(int playerNum)
{
	SceneManager::GetInstance().SetLanking(aliveCount_, playerNum);	// ランキングに登録
	aliveCount_--;	// 生存しているプレイヤーの数を減らす
}

void GameScene::ColisionWave(void)
{
	for (int i = 0; i < PLAYER_MAX;i++)	//ダメージを受ける側
	{
		auto& player1 = players_[i];
		if (player1->IsDeath() || !player1->IsLand())
		{	//死亡しているか、着地していないならスキップ
			continue;
		}

		for (int j = 0; j < PLAYER_MAX;j++)	//ダメージを与える側
		{
			if (i == j) { continue; }	//自分自身とは当たり判定しない
			auto& player2 = players_[j];
			float distance = Utility::Distance(player1->GetInitPos(), player2->GetInitPos());
			bool isHit = false;
			for (auto& waveRadius : player2->GetWaveRadius())
			{
				if (abs(distance - waveRadius) < PlayerBase::RADIUS)
				{
					player1->Damage(VSub(player1->GetInitPos(),player2->GetInitPos()));	//ダメージを受ける
					isHit = true;
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
	}
}

Vector2I GameScene::ShakePoint(void)
{
	Vector2I ret = {};

	if (shake_ > 0) {
		int size = shake_ / 5 % 2;
		size *= 2;
		size -= 1;
		switch (shakeKinds_)
		{
		case GameScene::WID:ret.x = size;
			break;
		case GameScene::HIG:ret.y = size;
			break;
		case GameScene::DIAG:ret = size;
			break;
		case GameScene::ROUND:
			size = shake_ / 3 % 12; size++;
			ret = { (int)((shakeSize_ * 1.5f) * cos(size * 30.0f)),(int)((shakeSize_ * 1.5f) * sin(size * 30.0f)) };
			break;
		}

		if (shakeKinds_ != ShakeKinds::ROUND) { ret *= shakeSize_; }

		DrawGraph(0, 0, mainScreen_, true);
	}

	return ret;
}
