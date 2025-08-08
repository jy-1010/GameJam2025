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
	SceneManager::GetInstance().InitLanking();	// �����L���O�̏�����
	// �q�b�g�X�g�b�v�J�E���^�[�̏�����
	hitStop_ = 0;

	// �X���[�J�E���^�[�̏�����
	slow_ = 0;
	slowInter_ = 5;

	aliveCount_ = PLAYER_MAX;	// �������Ă���v���C���[�̐���������

	// ��ʗh��֌W�̏�����-----------------------------------------------------------
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
	{	// �������Ă���v���C���[��1�l�ȉ��Ȃ�
		if (aliveCount_ == 1)
		{
			// �������Ă���v���C���[��1�l�Ȃ�
			for (int i = 0; i < PLAYER_MAX; i++)
			{
				if (players_[i] && !players_[i]->IsDeath())
				{	// �������Ă���v���C���[����������
					SceneManager::GetInstance().SetLanking(aliveCount_, i);	// �����L���O�ɓo�^
					break;
				}
			}
		}
		//���U���g�ւ̑J�ڏ���


		return;
	}

	limitTime_ -= SceneManager::GetInstance().GetDeltaTime();
	if (limitTime_ <= 0.0f) {
		// ���Ԑ؂�

	}
}
void GameScene::Draw(void)
{
	SetDrawScreen(mainScreen_);
	ClearDrawScreen();
	auto camera = SceneManager::GetInstance().GetCamera();
	camera.lock()->SetBeforeDraw();

	//�`�揈��-----------------------------------------
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
	DrawString(0, 0, "�Q�[���V�[��", 0xffffff);
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
	SceneManager::GetInstance().SetLanking(aliveCount_, playerNum);	// �����L���O�ɓo�^
	aliveCount_--;	// �������Ă���v���C���[�̐������炷
}

void GameScene::ColisionWave(void)
{
	for (int i = 0; i < PLAYER_MAX;i++)	//�_���[�W���󂯂鑤
	{
		auto& player1 = players_[i];
		if (player1->IsDeath() || !player1->IsLand())
		{	//���S���Ă��邩�A���n���Ă��Ȃ��Ȃ�X�L�b�v
			continue;
		}

		for (int j = 0; j < PLAYER_MAX;j++)	//�_���[�W��^���鑤
		{
			if (i == j) { continue; }	//�������g�Ƃ͓����蔻�肵�Ȃ�
			auto& player2 = players_[j];
			float distance = Utility::Distance(player1->GetInitPos(), player2->GetInitPos());
			bool isHit = false;
			for (auto& waveRadius : player2->GetWaveRadius())
			{
				if (abs(distance - waveRadius) < PlayerBase::RADIUS)
				{
					player1->Damage(VSub(player1->GetInitPos(),player2->GetInitPos()));	//�_���[�W���󂯂�
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
