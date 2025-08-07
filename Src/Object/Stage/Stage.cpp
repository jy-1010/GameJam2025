#include "Stage.h"

#include<DxLib.h>
#include <string>
#include<fstream>

#include"../../Utility/Utility.h"

Stage::Stage():
	buttonModel_(),
	models_(),
	blocks_()
{
}

Stage::~Stage()
{
}

void Stage::Load(void)
{
	int b = MV1LoadModel("Data/Model/Stage/Button.mv1");
	for (auto& botton : buttonModel_) { botton = MV1DuplicateModel(b); }

	models_[(int)TYPE::WOODEN] = MV1LoadModel("Data/Model/Stage/Wooden_Box.mv1");

	LoadMapData();

	for (int i = 0; i < 4; i++) {
		MV1SetPosition(buttonModel_[i], bottonPos_[i]);
	}
}

void Stage::Draw(void)
{
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

	for (auto& botton : buttonModel_) { MV1DeleteModel(botton); }
}

void Stage::LoadMapData(void)
{
	std::ifstream ifs = std::ifstream("Data/MapData/MapData.csv");
	if (!ifs) { return; }

	std::string line; // 1行の文字情報
	std::vector<std::string> strSplit; // 1行を1文字の動的配列に分割
	int z = 0;

	int bottonCou = 0;

	while (getline(ifs, line))
	{
		// １行をカンマ区切りで分割
		strSplit = Utility::Split(line, ',');

		for (int x = 0; x < strSplit.size(); x++) {
			if (std::stoi(strSplit[x]) == 100) {
				Block* block = new Block();
				block->Create((Block::TYPE)0, models_[0], x, z);
				blocks_.emplace_back(block);

				bottonPos_[bottonCou] = {
					x * Block::SIZE_BLOCK + (Block::SIZE_BLOCK / 2),
					0.0f,
					z * Block::SIZE_BLOCK + (Block::SIZE_BLOCK / 2)
				};
				bottonCou++;
			}
			else {
				Block* block = new Block();
				block->Create((Block::TYPE)0, models_[std::stoi(strSplit[x])], x, z);
				blocks_.emplace_back(block);
			}
		}

		z++;
	}
}
