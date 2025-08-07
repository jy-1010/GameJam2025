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

	// 1�u���b�N������̃T�C�Y
	static constexpr float SIZE_BLOCK = 100.0f;

	Block();
	~Block();

	void Create(TYPE type, int baseModelId, int mapX, int mapZ);
	void Draw(void);
	void Release(void);

private:
	// �u���b�N���
	TYPE type_;

	// ���f���̃n���h��ID
	int modelId_;
};

using TYPE = Block::TYPE;