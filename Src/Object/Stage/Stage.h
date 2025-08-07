#pragma once

#include<vector>

#include"Block.h"

class Stage
{
public:
	static constexpr VECTOR C_POS = { 1000.0f,1000.0f,-500.0f };

	Stage();
	~Stage();

	void Load(void);
	void Draw(void);
	void Release(void);

	std::vector<VECTOR>GetPos(void) { return bottonPos_; }
	const VECTOR GetCenter(void)const {
		return {
			((blockNum_.x / 2) * Block::SIZE_BLOCK),
			0.0f,
			((blockNum_.z / 2) * Block::SIZE_BLOCK)
		};
	}

private:
	int haikei_;
	int botton_;
	std::vector<int> buttonModel_;
	std::vector<VECTOR> bottonPos_;

	int models_[(int)TYPE::MAX];

	std::vector<Block*> blocks_;
	VECTOR blockNum_;
	void LoadMapData(void);
};