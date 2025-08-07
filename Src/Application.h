#pragma once
#include <string>
// �N���X�̑O���錾
class FPS;

class Application
{
public:
	// �X�N���[���T�C�Y
	static constexpr int SCREEN_SIZE_X = 1500;	// �X�N���[������;
	static constexpr int SCREEN_SIZE_Y = 960;	// �X�N���[���c��;

	// �f�[�^�p�X�֘A
//-------------------------------------------
	static const std::string PATH_IMAGE;
	static const std::string PATH_MODEL;
	//static const std::string PATH_EFFECT;
	static const std::string PATH_SOUND_BGM;
	static const std::string PATH_SOUND_SE;

	// �V���O���g���i�����E�擾�E�폜�j
	static void CreateInstance(void) { if (instance_ == nullptr) { instance_ = new Application(); instance_->Init(); } }
	static Application& GetInstance(void) { return *instance_; }
	static void DeleteInstance(void) { if (instance_ != nullptr) delete instance_; instance_ = nullptr; }

	void Init(void);	// ������
	void Run(void);		// �Q�[�����[�v�̊J�n
	void Release(void);	// ���

	// �����������^���s�̔���
	bool IsInitFail(void) const { return isInitFail_; };

	// ��������^���s�̔���
	bool IsReleaseFail(void) const { return isReleaseFail_; };

	void End(void) { isEnd_ = true; }

private:
	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	Application(void);

	// �f�X�g���N�^�����l
	~Application(void);

	// �ÓI�C���X�^���X
	static Application* instance_;

	// ���������s
	bool isInitFail_;

	// ������s
	bool isReleaseFail_;

	// FPS
	FPS* fps_;

	bool isEnd_;
};
