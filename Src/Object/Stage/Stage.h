#pragma once

#include<vector>

#include"Block.h"

class Stage
{
public:
	Stage();
	~Stage();

	void Load(void);
	void Draw(void);
	void Release(void);

private:
	int buttonModel_;
	int models_[(int)TYPE::MAX];

	std::vector<Block*> blocks_;
	void LoadMapData(void);
};