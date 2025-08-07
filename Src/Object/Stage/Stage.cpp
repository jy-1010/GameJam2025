#include "Stage.h"

#include<DxLib.h>
#include <string>
#include<fstream>

#include"../../Utility/Utility.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Load(void)
{
	buttonModel_ = MV1LoadModel("Data/Model/Stage/Button.mv1");

	models_[(int)TYPE::WOODEN] = MV1LoadModel("Data/Model/Stage/Wooden_Box.mv1");

	LoadMapData();
}

void Stage::Draw(void)
{
	for (auto& block : blocks_) { block->Draw(); }
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

	MV1DeleteModel(buttonModel_);
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
			Block* block = new Block();
			block->Create((Block::TYPE)0, models_[std::stoi(strSplit[x])], x, z);
			blocks_.emplace_back(block);
		}

		z++;
	}
}
