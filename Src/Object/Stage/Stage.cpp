#include "Stage.h"

#include<DxLib.h>
#include <string>
#include<fstream>

#include"../../Utility/Utility.h"
#include"../../Application.h"

Stage::Stage():
	haikei_(-1),
	botton_(),
	buttonModel_(),
	bottonPos_(),
	models_(),
	blocks_(),
	blockNum_()
{
}

Stage::~Stage()
{
}

void Stage::Load(void)
{
	haikei_ = Utility::LoadImg("Data/Image/Background.png");

	botton_ = MV1LoadModel("Data/Model/Stage/Button.mv1");

	models_[(int)TYPE::WOODEN] = MV1LoadModel("Data/Model/Stage/Wooden_Box.mv1");

	LoadMapData();
}

void Stage::Draw(void)
{
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 2, 0, haikei_, true);
	for (auto& block : blocks_) { block->Draw(); }
	for (auto& botton : buttonModel_) { MV1DrawModel(botton); }
}

void Stage::Release(void)
{
	for (auto& block : blocks_) {
		if (!block) { continue; }
		block->Release();
		delete block;
		block = nullptr;
	}
	blocks_.clear();

	for (auto& model : models_) { MV1DeleteModel(model); }

	bottonPos_.clear();
	for (auto& botton : buttonModel_) { MV1DeleteModel(botton); }
	buttonModel_.clear();
	MV1DeleteModel(botton_);
	DeleteGraph(haikei_);
}



void Stage::LoadMapData(void)
{
	std::ifstream ifs = std::ifstream("Data/MapData/MapData.csv");
	if (!ifs) { return; }

	std::string line; // 1行の文字情報
	std::vector<std::string> strSplit; // 1行を1文字の動的配列に分割
	int z = 0;

	while (getline(ifs, line))
	{
		// １行をカンマ区切りで分割
		strSplit = Utility::Split(line, ',');

		for (int x = 0; x < strSplit.size(); x++) {
			if (std::stoi(strSplit[x]) == 100) {
				Block* block = new Block();
				block->Create((Block::TYPE)0, models_[0], x, z);
				blocks_.emplace_back(block);

				buttonModel_.emplace_back(MV1DuplicateModel(botton_));
				bottonPos_.emplace_back(VGet(
					x * Block::SIZE_BLOCK + (Block::SIZE_BLOCK / 2),
					0.0f,
					z * Block::SIZE_BLOCK + (Block::SIZE_BLOCK / 2)
				));
				MV1SetPosition(buttonModel_[buttonModel_.size() - 1], bottonPos_[bottonPos_.size() - 1]);
			}
			else {
				Block* block = new Block();
				block->Create((Block::TYPE)0, models_[std::stoi(strSplit[x])], x, z);
				blocks_.emplace_back(block);
			}
		}

		z++;
	}
	blockNum_.x = strSplit.size();
	blockNum_.z = z;
}
