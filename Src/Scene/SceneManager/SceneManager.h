#pragma once

#include<memory>
#include<list>

#include <chrono>

#include "../Game/GameScene.h"

class SceneBase;
class Camera;

class SceneManager
{
public:
	// �V�[���Ǘ��p
	enum class SCENE_ID
	{
		NONE = -1,

		TITLE,
		GAME,
		RESULT,

		MAX
	};

	// �V���O���g���i�����E�擾�E�폜�j
	static void CreateInstance(void) { if (instance_ == nullptr) { instance_ = new SceneManager(); } };
	static SceneManager& GetInstance(void) { return *instance_; };
	static void DeleteInstance(void) { if (instance_ != nullptr) { delete instance_; instance_ = nullptr; } }

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
	bool GetGameEnd(void) { return isGameEnd_; }

	// �f���^�^�C���̎擾
	float GetDeltaTime(void) const;
	void ResetDeltaTime(void);

	// �Q�[���I���擾
	

	std::weak_ptr<Camera> GetCamera(void) { return camera_; }

	// �����L���O�̎擾
	int GetLanking(int lankNum) const { return lanking_[lankNum - 1]; }
	// �����L���O�̐ݒ�
	void SetLanking(int lankNum, int playerNum) { lanking_[lankNum - 1] = playerNum + 1; }
	// �����L���O�̏�����
	void InitLanking(void) { for (int i = 0; i < GameScene::PLAYER_MAX; i++) { lanking_[i] = 0; } }
	// 1�ʂ����l���邩�̐ݒ�
	void SetTopNum(int num) { topNum_ = num; }
	int GetTopNum(void) { return topNum_; }


	std::list<std::shared_ptr<SceneBase>>GetScenes(void) { return scenes_; }

private:
	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	SceneManager(void);
	// �f�X�g���N�^�����l
	~SceneManager(void);

	//// �R�s�[�E���[�u������֎~
	//SceneManager(const SceneManager&) = delete;
	//SceneManager& operator=(const SceneManager&) = delete;
	//SceneManager(SceneManager&&) = delete;
	//SceneManager& operator=(SceneManager&&) = delete;

	// ���L���R���p�C���G���[�����邽�� ��L��ǉ�
	// SceneManager copy = *SceneManager::GetInstance();
	// SceneManager copied(*SceneManager::GetInstance());
	// SceneManager moved = std::move(*SceneManager::GetInstance());
	// 
	// �ÓI�C���X�^���X
	static SceneManager* instance_;

	//Draw�̊֌W��Back���ŐV�̃V�[���Ƃ���
	//��{�I�ɂ͗v�f�͈���������|�[�Y�V�[���Ȃǂ��ςݏd�Ȃ�`
	std::list<std::shared_ptr<SceneBase>>scenes_;

	// �f���^�^�C��
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	// �V�[��ID
	SCENE_ID sceneId_;

	// �Q�[���I��
	bool isGameEnd_;

	std::shared_ptr<Camera> camera_;

	int lanking_[GameScene::PLAYER_MAX];
	int topNum_;

};

using SCENE_ID = SceneManager::SCENE_ID;