#pragma once
#include <vector>
#include <map>
#include <memory>
#include "../../Common/Vector2.h"

class InputManager;

class KeyConfig
{
public:

	// �Q�[���R���g���[���[�̔F���ԍ�
	// DxLib�萔�ADX_INPUT_PAD1���ɑΉ�
	enum class JOYPAD_NO
	{
		KEY_PAD1,			// �L�[���͂ƃp�b�h�P����
		PAD1,				// �p�b�h�P����
		PAD2,				// �p�b�h�Q����
		PAD3,				// �p�b�h�R����
		PAD4,				// �p�b�h�S����
		INPUT_KEY = 4096	// �L�[����
	};

	enum class TYPE
	{
		KEYBORD_MOUSE,
		PAD,
		ALL,
	};


	// �Q�[���R���g���[���[�{�^��
	enum class JOYPAD_BTN
	{
		RIGHTBUTTON_LEFT = 0,	// X
		RIGHTBUTTON_RIGHT,		// B
		RIGHTBUTTON_TOP,		// Y
		RIGHTBUTTON_DOWN,		// A
		R_TRIGGER,				// R_TRIGGER
		L_TRIGGER,				// L_TRIGGER
		R_BUTTON,				// R_BUTTON
		L_BUTTON,				// L_BUTTON
		START_BUTTON,			// START_BUTTON
		SELECT_BUTTON,			// SELECT_BUTTON
		LEFTBUTTON_TOP,			// ��
		LEFTBUTTON_DOWN,		// ��
		LEFTBUTTON_LEFT,		// ��
		LEFTBUTTON_RIGHT,		// �E
		LEFT_STICK,				// ���X�e�B�b�N��������
		RIGHT_STICK,			// �E�X�e�B�b�N��������
		MAX
	};

	enum class JOYPAD_STICK
	{
		L_STICK_UP,		//���X�e�B�b�N��
		L_STICK_DOWN,	//���X�e�B�b�N��
		L_STICK_LEFT,	//���X�e�B�b�N��
		L_STICK_RIGHT,	//���X�e�B�b�N�E
		R_STICK_UP,		//�E�X�e�B�b�N��
		R_STICK_DOWN,	//�E�X�e�B�b�N��
		R_STICK_LEFT,	//�E�X�e�B�b�N��
		R_STICK_RIGHT,	//�E�X�e�B�b�N�E
		MAX
	};

	enum class MOUSE
	{
		CLICK_RIGHT,		//�E�N���b�N
		CLICK_LEFT,			//���N���b�N
		MOVE_LEFT,			//���ړ�
		MOVE_RIGHT,			//�E�ړ�
		MOVE_UP,			//��ړ�
		MOVE_DOWN,			//���ړ�
		WHEEL_FRONT,		//�z�C�[���O(��)��]
		WHEEL_BACK,			//�z�C�[�����(��O)��]
		MAX
	};

	enum class CONTROL_TYPE //����̎��	
	{
		CHENGE_SCENE,
		FAST_JUMP,
		MIDIUM_JUMP,
		SLOW_JUMP,
		JUMP,
		SERECT_RIFHT,
		SERECT_LEFT,
		DECISION,
		EXITDECISION,
		END,
		MAX,
	};

	// �C���X�^���X�𖾎��I�ɐ���
	static void CreateInstance(void);

	// �C���X�^���X�̎擾
	static KeyConfig& GetInstance(void);

	void Init(void);
	void Update(void);

	//����̎�ޕʂɃL�[�̏�Ԃ��擾
	bool IsNew(CONTROL_TYPE cType, KeyConfig::JOYPAD_NO no ,TYPE type = TYPE::ALL);
	bool IsTrgDown(CONTROL_TYPE cType, KeyConfig::JOYPAD_NO no,TYPE type = TYPE::ALL);
	bool IsTrgUp(CONTROL_TYPE cType, KeyConfig::JOYPAD_NO no, TYPE type = TYPE::ALL);

	//����̎�ޕʂɃL�[��ǉ�	
	void Add(CONTROL_TYPE type, int key);
	void Add(CONTROL_TYPE type, JOYPAD_BTN key);
	void Add(CONTROL_TYPE type, JOYPAD_STICK key);
	void Add(CONTROL_TYPE type, MOUSE key);

	// �}�E�X���W�̎擾
	Vector2I GetMousePos(void) const;
	//�}�E�X�̈ړ��ʂ��擾
	Vector2I GetMouseMove(void) const;

	//�}�E�X�̍��W��ݒ�
	void SetMousePosScreen(void);

	void SetMousePos(const Vector2I& pos);
	float GetLStickDeg(KeyConfig::JOYPAD_NO no) const;

	float GetRStickDeg(KeyConfig::JOYPAD_NO no) const;
	//���0.0�x�Ƃ��Ċp�x��n��
	Vector2 GetKnockLStickSize(KeyConfig::JOYPAD_NO no) const;
	Vector2 GetKnockRStickSize(KeyConfig::JOYPAD_NO no) const;
	//�w��̕����ɓ|�ꂽ�x����0����1000
	int PadStickOverSize(KeyConfig::JOYPAD_NO no, KeyConfig::JOYPAD_STICK stick)const;
	// ���\�[�X�̔j��
	void Destroy(void);
	/// <summary>
	/// �p�b�h��U������
	/// </summary>
	/// <param name="_no">�U��������PAD�ԍ�</param>
	/// <param name="_time">�~���b�@,-1�Ŗ����ɑ����邱�Ƃ��ł���(STOP �K�{)</param>
	/// <param name="_pow">1�`1000</param>
	void PadVibration(KeyConfig::JOYPAD_NO _no, int _time, int _pow);
	/// <summary>
	/// �U�����~�߂�
	/// </summary>
	/// <param name="_no"></param>
	void StopPadVibration(KeyConfig::JOYPAD_NO _no);
private:
	std::unique_ptr<InputManager> inputManager_;	//���͊Ǘ��N���X�̃C���X�^���X

	std::map<CONTROL_TYPE, std::vector<int>>keyInput_;								//����̎�ނƃL�[�̎�ނŃL�[�{�[�h�̏�Ԃ��i�[
	std::map<CONTROL_TYPE, std::vector<JOYPAD_BTN>>conInput_;			//����̎�ނƃ{�^���̎�ނŃR���g���[���[�̏�Ԃ��i�[
	std::map<CONTROL_TYPE, std::vector<JOYPAD_STICK>>stickInput_;		//����̎�ނƃX�e�B�b�N�̎�ނŃR���g���[���[�̏�Ԃ��i�[
	std::map < CONTROL_TYPE, std::vector<MOUSE>>mouseInput_;			//����̎�ނƃ}�E�X�̎�ނŃ}�E�X�̏�Ԃ��i�[

	// �V���O���g���p�C���X�^���X
	static KeyConfig* instance_;

	KeyConfig(void);
	KeyConfig(const KeyConfig& manager);
	~KeyConfig(void) = default;
};

