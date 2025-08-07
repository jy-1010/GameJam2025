#pragma once
#include <map>
#include <vector>
#include <Dxlib.h>
#include "../../Common/Vector2.h"
#include "KeyConfig.h"

class InputManager
{

public:

	static constexpr int STICK_THRESHOLD = 300;	//�X�e�B�b�N�̗P�\

	// �Q�[���R���g���[���[�^�C�v
	// DxLib�萔�ADX_OTHER���ɑΉ�
	enum class JOYPAD_TYPE
	{
		OTHER = 0,
		XBOX_360,
		XBOX_ONE,
		DUAL_SHOCK_4,
		DUAL_SENSE,
		SWITCH_JOY_CON_L,
		SWITCH_JOY_CON_R,
		SWITCH_PRO_CTRL,
		MAX
	};
	// �Q�[���R���g���[���[�̓��͏��
	struct JOYPAD_IN_STATE
	{
		unsigned char ButtonsOld[static_cast<int>(KeyConfig::JOYPAD_BTN::MAX)];
		unsigned char ButtonsNew[static_cast<int>(KeyConfig::JOYPAD_BTN::MAX)];
		bool IsOld[static_cast<int>(KeyConfig::JOYPAD_BTN::MAX)];
		bool IsNew[static_cast<int>(KeyConfig::JOYPAD_BTN::MAX)];
		bool IsTrgDown[static_cast<int>(KeyConfig::JOYPAD_BTN::MAX)];
		bool IsTrgUp[static_cast<int>(KeyConfig::JOYPAD_BTN::MAX)];
		int AKeyLX;
		int AKeyLY;
		int AKeyRX;
		int AKeyRY;
	};
	InputManager(void);
	InputManager(const InputManager& manager) = default;
	~InputManager(void);

	// �C���X�^���X�𖾎��I�ɐ���
	static void CreateInstance(void);

	// �C���X�^���X�̎擾
	static InputManager& GetInstance(void);

	void Init(void);
	void Update(void);
	void Release(void);

	// ������s���L�[��ǉ�
	void Add(int key);

	// ������s���L�[���N���A
	void Clear(void);

	// �L�[�̉�������
	bool IsNew(int key) const;

	// �L�[�̉�������(�������ςȂ���NG)
	bool IsTrgDown(int key) const;

	// �L�[�𗣂������̔���
	bool IsTrgUp(int key) const;

	// �}�E�X���W�̎擾
	Vector2I GetMousePos(void) const;

	//�}�E�X�̈ړ��������擾
	Vector2I GetMousePosDistance(void)const;

	//�}�E�X�̍��W��ݒ�
	void SetMousePosScreen(void);

	void SetMousePos(const Vector2I& pos);

	// �}�E�X�̃N���b�N��Ԃ��擾(MOUSE_INPUT_LEFT�ARIGHT)
	int GetMouse(void) const;

	// �R���g���[���̓��͏����擾����
	JOYPAD_IN_STATE GetJPadInputState(KeyConfig::JOYPAD_NO no);

	// �{�^���������ꂽ
	bool IsPadBtnNew(KeyConfig::JOYPAD_NO no, KeyConfig::JOYPAD_BTN btn) const;
	bool IsPadBtnTrgDown(KeyConfig::JOYPAD_NO no, KeyConfig::JOYPAD_BTN btn) const;
	bool IsPadBtnTrgUp(KeyConfig::JOYPAD_NO no, KeyConfig::JOYPAD_BTN btn) const;

	// �X�e�B�b�N���|���ꂽ��
	bool IsStickNew(KeyConfig::JOYPAD_NO no, KeyConfig::JOYPAD_STICK stick) const;
	bool IsStickDown(KeyConfig::JOYPAD_NO no, KeyConfig::JOYPAD_STICK stick) const;
	bool IsStickUp(KeyConfig::JOYPAD_NO no, KeyConfig::JOYPAD_STICK stick) const;

	bool IsMouseNew(KeyConfig::MOUSE mouse);
	bool IsMouseTrgUp(KeyConfig::MOUSE mouse);
	bool IsMouseTrgDown(KeyConfig::MOUSE mouse);
private:

	// �L�[���
	struct Info
	{
		int key;			// �L�[ID
		bool keyOld;		// 1�t���[���O�̉������
		bool keyNew;		// ���t���[���̉������
		bool keyTrgDown;	// ���t���[���Ń{�^���������ꂽ��
		bool keyTrgUp;		// ���t���[���Ń{�^���������ꂽ��
	};

	// �}�E�X
	struct MouseInfo
	{
		bool keyOld = false;		// 1�t���[���O�̉������
		bool keyNew = false;		// ���t���[���̉������
		bool keyTrgDown = false;	// ���t���[���Ń{�^���������ꂽ��
		bool keyTrgUp = false;		// ���t���[���Ń{�^���������ꂽ��
	};

	struct StickInfo
	{
		KeyConfig::JOYPAD_STICK key;
		bool keyOld = false;
		bool keyNew = false;
		bool keyTrgDown = false;
		bool keyTrgUp = false;
	};

	// �R���g���[�����
	DINPUT_JOYSTATE joyDInState_;

	// �R���g���[�����(XBOX)
	XINPUT_STATE joyXInState_;

	// �V���O���g���p�C���X�^���X
	static InputManager* instance_;

	// �L�[���
	std::map<int, InputManager::Info> keyInfos_;
	InputManager::Info infoEmpty_;

	// �}�E�X���
	std::map<KeyConfig::MOUSE, InputManager::MouseInfo> mouseInfos_;
	InputManager::MouseInfo mouseInfoEmpty_;

	// �X�e�B�b�N���
	std::map<KeyConfig::JOYPAD_NO, std::vector<InputManager::StickInfo>> stickInfos_;

	// �}�E�X�J�[�\���̈ʒu
	Vector2I mousePrePos_;
	Vector2I mousePos_;
	
	//�}�E�X�z�C�[����]��
	int wheelRot_;

	// �}�E�X�{�^���̓��͏��
	int mouseInput_;

	// �p�b�h���
	JOYPAD_IN_STATE padInfos_[5];

	// �z��̒�����L�[�����擾����
	const InputManager::Info& Find(int key) const;

	// �z��̒�����}�E�X�����擾����
	const InputManager::MouseInfo& FindMouse(KeyConfig::MOUSE key) const;

	// �ڑ����ꂽ�R���g���[���̎�ʂ��擾����
	JOYPAD_TYPE GetJPadType(KeyConfig::JOYPAD_NO no);

	// �R���g���[���̓��͏����擾����
	DINPUT_JOYSTATE GetJPadDInputState(KeyConfig::JOYPAD_NO no);

	// �R���g���[��(XBOX)�̓��͏����擾����
	XINPUT_STATE GetJPadXInputState(KeyConfig::JOYPAD_NO no);

	// �R���g���[���̓��͏����X�V����
	void SetJPadInState(KeyConfig::JOYPAD_NO jpNo);

};