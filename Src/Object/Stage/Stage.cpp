#include "Stage.h"

#include<DxLib.h>

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Load(void)
{

}

void Stage::Draw(void)
{
	for (auto& map : mapData_) {
		for (auto& m : map) {
			MV1DrawModel(m);
		}
	}
}

void Stage::Release(void)
{
	mapData_.clear();

	for (auto& block : blocks_) { MV1DeleteModel(block); }
	blocks_.clear();
}