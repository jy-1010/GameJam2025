#pragma once
#include <DxLib.h>
#include "../../Common/Quaternion.h"
#include "../Input/KeyConfig.h"
class Transform;

class Camera
{

public:

	// �J�����X�s�[�h(�x)
	static constexpr float SPEED = 1.0f;
	static constexpr float SPEED_PAD = 0.0015f;
	static constexpr float SPEED_MOUSE = 0.05f;

	//�J�����Y�[���X�s�[�h
	static constexpr float ZOOM_SPEED = 5.0f;

	//�J�����̃Y�[���͈�
	static constexpr float ZOOM_RADIUS = 300.0f;
	// �J�����N���b�v�FNEAR
	static constexpr float CAMERA_NEAR = 10.0f;

	// �J�����N���b�v�FNEAR
	static constexpr float CAMERA_FAR = 30000.0f;

	// �J�����̏������W
	static constexpr VECTOR DEFAULT_CAMERA_POS = { 0.0f, 100.0f, -500.0f };

	// �Ǐ]�ʒu����J�����ʒu�܂ł̑��΍��W
	static constexpr VECTOR LOCAL_F2C_POS = { 0.0f, 0.0f, -400.0f };
	//static constexpr VECTOR LOCAL_F2C_POS = { 0.0f, -1000.0f, -200.0f };

	//FPS�̎��̑��΍��W
	static constexpr VECTOR FPS_LOCAL_F2C_POS = { 0.0f, 130.0f, 20.0f };

	//FPS�p
	static constexpr VECTOR FPS_LOCAL_F2T_POS = { 0.0f, 0.0f, 2000.0f };

	//�Œ��p
	static constexpr VECTOR FIXED_LOCAL_P2T_POS = { 0.0f, -1500.0f, 0.0f };

	//�΂ߏ�p
	static constexpr VECTOR FIXED_DIAGONAL_TARGET_POS = { 2000.0f, 00.0f, 3000.0f };

	// �Ǐ]�ʒu���璍���_�܂ł̑��΍��W
	static constexpr VECTOR LOCAL_F2T_POS = { 0.0f, 0.0f, 100.0f };

	// �J������X��]����x�p
	static constexpr float LIMIT_X_UP_RAD = 60.0f * (DX_PI_F / 180.0f);
	static constexpr float LIMIT_X_DW_RAD = 15.0f * (DX_PI_F / 180.0f);

	//FPS�̏���p
	static constexpr float FPS_LIMIT_X_UP_RAD = -80.0f * (DX_PI_F / 180.0f);
	static constexpr float FPS_LIMIT_X_DW_RAD = 70.0f * (DX_PI_F / 180.0f);

	
	// �J�������[�h
	enum class MODE
	{
		NONE,
		FIXED_POINT,
		FOLLOW,
		FOLLOW_ROTATION,	//�����イ���Ȃ��玩����]����s�\
		//SELF_SHOT,
		//FPS,
		FREE_CONTROLL,
		FIXED_UP,
		FIXED_DIAGONAL,	//�΂ߌŒ�
	};



	Camera(int _playerNum);
	~Camera(void);

	void Init(void);
	void Update(void);
	void SetBeforeDraw(void);
	void Draw(void);

	// �J�����ʒu
	VECTOR GetPos(void) const;
	// �J�����̑���p�x
	VECTOR GetAngles(void) const;
	// �J�����̒����_
	VECTOR GetTargetPos(void) const;

	// �J�����p�x
	Quaternion GetQuaRot(void) const;
	// X��]�𔲂����J�����p�x
	Quaternion GetQuaRotOutX(void) const;
	// �J�����̑O������
	VECTOR GetForward(void) const;

	//�J�����̐ݒ�
	void CameraSetting(void);

	// �J�������[�h�̕ύX
	void ChangeMode(MODE mode);

	MODE GetMode(void) { return mode_; }

	// �Ǐ]�Ώۂ̐ݒ�
	void SetFollow(const Transform* follow);

	void SetPos(VECTOR pos) { pos_ = pos; }
	void SetAngles(VECTOR angles) { angles_ = angles; }
	void SetTargetPos(VECTOR pos) { targetPos_ = pos; }
private:

	// �J�����̃��[�J�����W
	VECTOR localPos_;

	// �J�������Ǐ]�ΏۂƂ���Transform
	const Transform* followTransform_;

	//PAD�̔ԍ�
	KeyConfig::JOYPAD_NO padNo_;

	// �J�������[�h
	MODE mode_;

	// �J�����̈ʒu
	VECTOR pos_= {0.0f,0.0f,0.0f};

	// �J�����p�x(rad)
	VECTOR angles_;

	// X����]�������p�x
	Quaternion rotOutX_;

	// �J�����p�x
	Quaternion rot_;

	// �����_
	VECTOR targetPos_;

	// �J�����̏����
	VECTOR cameraUp_;

	// �J�����������ʒu�ɖ߂�
	void SetDefault(void);

	// �Ǐ]�ΏۂƂ̈ʒu���������
	//void SyncFollow(void);

	//FPS�p�̈ʒu����
	//void SyncFollowFPS(void);

	// �J��������
	//void ProcessRot(void);
	//void ProcessZoom(void);
	//�}�E�X�ł̃J��������
	//void ProcessRotMause(float* x_m, float* y_m, const float fov_per = 1.0f);
	// ���[�h�ʍX�V�X�e�b�v
	void SetBeforeDrawFixedPoint(void);
	void SetBeforeDrawFollow(void);
	//void SetBeforeDrawFollowRotation(void);
	//void SetBeforeDrawSelfShot(void);
	//void SetBeforeDrawFPS(void);
	void SetBeforeDrawFreeControll(void);
	void SetBeforeDrawFixedUp(void);
	void SetBeforeDrawFixedDiagonal(void);
};

