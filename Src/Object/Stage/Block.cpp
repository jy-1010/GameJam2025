#include "Block.h"



Block::Block()
{
}

Block::~Block()
{
}

void Block::Create(TYPE type, int baseModelId, int mapX, int mapZ)
{
	// �u���b�N�̎��
	type_ = type;

	// ���f���̃n���h��ID
	modelId_ = MV1DuplicateModel(baseModelId);


	// 1�u���b�N������̔����̑傫��
	const float SIZE_HALF_BLOCK = (SIZE_BLOCK / 2.0f);

	// �����Ŏw�肳�ꂽ�}�b�v���W������W���v�Z����
	// ����̂R�c���f���̒��S���W�́A�u���b�N�̒��S�Ɉʒu����
	float x = static_cast<float>(mapX);
	float z = static_cast<float>(mapZ);

	VECTOR pos = VGet(
		x * SIZE_BLOCK + SIZE_HALF_BLOCK,
		-SIZE_HALF_BLOCK,
		z * SIZE_BLOCK + SIZE_HALF_BLOCK
	);

	// ���W�ݒ�
	MV1SetPosition(modelId_, pos);

	// �傫���ݒ�
	MV1SetScale(modelId_, SCALES);


	MV1SetupCollInfo(modelId_, -1);
}

void Block::Draw(void)
{
	// ���f���̕`��
	MV1DrawModel(modelId_);
}
void Block::Release(void)
{
	MV1DeleteModel(modelId_);
}
