#pragma once

#include<DxLib.h>

class Block
{
public:
	enum class TYPE {
		NON = -1,

		WOODEN,

		MAX
	};

	static constexpr VECTOR SCALES = { 0.5f, 0.5f, 0.5f };

	// 1ブロックあたりのサイズ
	static constexpr float SIZE_BLOCK = 100.0f;

	Block();
	~Block();

	void Create(TYPE type, int baseModelId, int mapX, int mapZ);
	void Draw(void);
	void Release(void);

private:
	// ブロック種別
	TYPE type_;

	// モデルのハンドルID
	int modelId_;
};

using TYPE = Block::TYPE;