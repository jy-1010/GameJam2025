#pragma once
#include <map>
#include <vector>
#include <memory>
#include "Sound.h"

class SoundManager
{
public:
	//���\�[�X��
	enum class SRC
	{
		TITLE_BGM,		//�^�C�g���V�[����BGM

		HIPDROP_SE,	//���艹

		MAX

	};
	enum class SOUND_TYPE
	{
		BGM,
		SE,
	};
	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static SoundManager& GetInstance(void);

	// ������
	void Init(void);

	// ���(�V�[���ؑ֎��Ɉ�U���)
	void Release(void);

	// ���\�[�X�̊��S�j��
	void Destroy(void);

	/// <summary>
	/// �񎟌������Đ�
	/// </summary>
	/// <param name="src">���̎��</param>
	/// <param name="times">�P�񂩃��[�v��</param>
	/// <returns>�Đ�������������true</returns>
	bool Play(SRC src,Sound::TIMES times);

	/// <summary>
	/// �O���������Đ�
	/// </summary>
	/// <param name="src">���̎��</param>
	/// <param name="times">�P�񂩃��[�v��</param>
	/// <param name="pos">�Đ�����ꏊ</param>
	/// <param name="radius">������������͈�</param>
	/// <returns>�Đ�����������true</returns>
	bool Play(SRC src,Sound::TIMES times,VECTOR pos, float radius);

	/// <summary>
	/// �w��̉������ׂĒ�~����
	/// </summary>
	/// <param name="src">���̎��</param>
	void Stop(SRC src);

	/// <summary>
	/// �w��̉���1�ł��Ȃ��Ă��邩�ǂ���
	/// </summary>
	/// <param name="src">���̎��</param>
	/// <returns>�P�ł��Ȃ��Ă�����true</returns>
	bool CheckMove(SRC src);

	/// <summary>
	/// �w�肵�����̉��ʂ�S�ĕς���
	/// </summary>
	/// <param name="src">���̎��</param>
	/// <param name="per">0.0�`1.0�Ńp�[�Z���g��ݒ�</param>
	void ChengeVolume(SRC src, float per);

	/// <summary>
	/// 3D�����̎��̈ʒu�ƑO���x�N�g����ݒ肷��
	/// </summary>
	/// <param name="pos">���̈ʒu(�J�������W)</param>
	/// <param name="frontPos">�O������(�J���������_)</param>
	void Set3DListenPosAndFrontPos(VECTOR pos, VECTOR frontPos);

private:
	// �ÓI�C���X�^���X
	static SoundManager* instance_;
	//BGM��SE�ɕ�����
	std::map<SOUND_TYPE, std::vector<SRC>> soundType_;
	//�����ő�Đ���
	std::map<SRC, int> maxPlayNum;
	//�ǂݍ��ݍς݃��\�[�X
	std::map<SRC, std::shared_ptr<Sound>> loadMap_;
	//�v���C�p
	std::map<SRC, std::vector<std::shared_ptr<Sound>>> playMap_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	SoundManager(void) = default;

	// �f�X�g���N�^�����l
	~SoundManager(void) = default;
};

