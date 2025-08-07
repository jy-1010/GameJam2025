#pragma once

class Loading
{
public:
	// �V���O���g���i�����E�擾�E�폜�j
	static void CreateInstance(void) { if (instance_ == nullptr) { instance_ = new Loading(); } };
	static Loading* GetInstance(void) { return instance_; };
	static void DeleteInstance(void) { if (instance_ != nullptr) { delete instance_; instance_ = nullptr; } }

private:
	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	Loading();
	~Loading();

	// �R�s�[�E���[�u������֎~
	Loading(const Loading&) = delete;
	Loading& operator=(const Loading&) = delete;
	Loading(Loading&&) = delete;
	Loading& operator=(Loading&&) = delete;

	// ���L���R���p�C���G���[�����邽�� ��L��ǉ�
	// Loading copy = *Loading::GetInstance();
	// Loading copied(*Loading::GetInstance());
	// Loading moved = std::move(*Loading::GetInstance());
public:

	void Init(void);		// ������
	void Load(void);		// �ǂݍ���
	void Update(void);		// �X�V
	void Draw(void);		// �`��
	void Release(void);		// ���

	void StartAsyncLoad(void);	// �񓯊����[�h�̊J�n
	void EndAsyncLoad(void);	// �񓯊����[�h�̏I��

	// ���[�h������Ԃ��B
	bool IsLoading(void) { return isLoading_; }

private:

	// �ÓI�C���X�^���X
	static Loading* instance_;

	// �Œ�ł����[�h��ʂ�\�����鎞��
	static constexpr int MIN_LOAD_TIME = 60;	// 60fps(1�b) * x

	// �摜�n���h��
	int handle_[7];
	int animCounter_;
	int animInterval_;

	// ���W
	int posX_;	// X���W
	int posY_;	// Y���W

	// ���[�h���̔���p
	bool isLoading_;

	// �Œ�ł����[�h��ʂ�\�����鎞�Ԃ͈̔�
	int loadTimer_;
};
