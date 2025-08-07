#include "Block.h"



Block::Block()
{
}

Block::~Block()
{
}

void Block::Create(TYPE type, int baseModelId, int mapX, int mapZ)
{
	// ブロックの種類
	type_ = type;

	// モデルのハンドルID
	modelId_ = MV1DuplicateModel(baseModelId);


	// 1ブロックあたりの半分の大きさ
	const float SIZE_HALF_BLOCK = (SIZE_BLOCK / 2.0f);

	// 引数で指定されたマップ座標から座標を計算する
	// 今回の３Ｄモデルの中心座標は、ブロックの中心に位置する
	float x = static_cast<float>(mapX);
	float z = static_cast<float>(mapZ);

	VECTOR pos = VGet(
		x * SIZE_BLOCK + SIZE_HALF_BLOCK,
		-SIZE_HALF_BLOCK,
		z * SIZE_BLOCK + SIZE_HALF_BLOCK
	);

	// 座標設定
	MV1SetPosition(modelId_, pos);

	// 大きさ設定
	MV1SetScale(modelId_, SCALES);


	MV1SetupCollInfo(modelId_, -1);
}

void Block::Draw(void)
{
	// モデルの描画
	MV1DrawModel(modelId_);
}
void Block::Release(void)
{
	MV1DeleteModel(modelId_);
}
