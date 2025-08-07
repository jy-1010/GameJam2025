#pragma once

#include<memory>
#include<list>

class SceneBase;

class SceneManager
{
public:
	// �V�[���Ǘ��p
	enum class SCENE_ID
	{
		NONE = -1,

		TITLE,
		GAME,

		MAX
	};

public:
	// �V���O���g���i�����E�擾�E�폜�j
	static void CreateInstance(void) { if (instance_ == nullptr) { instance_ = new SceneManager(); } };
	static SceneManager& GetInstance(void) { return *instance_; };
	static void DeleteInstance(void) { if (instance_ != nullptr) { delete instance_; instance_ = nullptr; } }

private:
	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	SceneManager(void);
	// �f�X�g���N�^�����l
	~SceneManager(void);

	// �R�s�[�E���[�u������֎~
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;

	// ���L���R���p�C���G���[�����邽�� ��L��ǉ�
	// SceneManager copy = *SceneManager::GetInstance();
	// SceneManager copied(*SceneManager::GetInstance());
	// SceneManager moved = std::move(*SceneManager::GetInstance());
public:

	void Init(void);	// ������
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	void Release(void);	// ���

	// ��ԑJ��
	void ChangeScene(std::shared_ptr<SceneBase>scene);
	void ChangeScene(SCENE_ID scene);

	// �V�[����V�����ς�
	void PushScene(std::shared_ptr<SceneBase>scene);
	void PushScene(SCENE_ID scene);

	// �Ō�ɒǉ������V�[�����폜����B
	void PopScene(void);

	// �����I�ɓ���̃V�[���ɔ�ԁB���Z�b�g����������̃V�[���݂̂ɂ���B
	void JumpScene(std::shared_ptr<SceneBase>scene);
	void JumpScene(SCENE_ID scene);

	// �V�[��ID�̎擾
	SCENE_ID GetSceneID(void) const { return sceneId_; };

	// �Q�[���I��
	void GameEnd(void) { isGameEnd_ = true; }

	// �Q�[���I���擾
	bool GetGameEnd(void) { return isGameEnd_; }

private:
	// �ÓI�C���X�^���X
	static SceneManager* instance_;

	//Draw�̊֌W��Back���ŐV�̃V�[���Ƃ���
	//��{�I�ɂ͗v�f�͈���������|�[�Y�V�[���Ȃǂ��ςݏd�Ȃ�`
	std::list<std::shared_ptr<SceneBase>>scenes_;

	// �V�[��ID
	SCENE_ID sceneId_;

	// �Q�[���I��
	bool isGameEnd_;
};

using SCENE_ID = SceneManager::SCENE_ID;