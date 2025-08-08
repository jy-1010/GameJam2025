#pragma once
#include <memory>;
#include"../SceneBase.h"

#include"../../Common/Vector2.h"

class Stage;
class PlayerBase;

class GameScene : public SceneBase
{
public:

	static constexpr int PLAYER_MAX = 4;	// �v���C���[�̍ő吔

	static constexpr int LIMIT_TIME = 60;

	GameScene();
	~GameScene()override;

	// �ǂݍ���
	void Load(void)override;
	// ����������
	void Init(void)override;
	// �X�V�X�e�b�v
	void Update(void)override;
	// �`�揈��
	void Draw(void)override;
	// �������
	void Release(void)override;


	// �q�b�g�X�g�b�v���o
	static void HitStop(int time = 20) { hitStop_ = time; }

	// �X���[���o
	static void Slow(int time = 10, int inter = 5) { slow_ = time; slowInter_ = inter; }

	// ��ʗh��̎��
	enum ShakeKinds { WID/*���h��*/, HIG/*�c�h��*/, DIAG/*�΂ߗh��*/, ROUND/*���邭��*/ };
	// ��ʗh��̑傫��
	enum ShakeSize { SMALL = 3/*������*/, MEDIUM = 5/*�����炢*/, BIG = 8, /*�傫��*/ };

	/// <summary>
	/// ��ʗh�炵
	/// </summary>
	/// <param name="kinds">�h���(enum ShakeKinds ���g�p)</param>
	/// <param name="size">�h���傫��(enum ShakeSize ���g�p)</param>
	/// <param name="time">�h��鎞��(�t���[����)</param>
	static void Shake(ShakeKinds kinds = ShakeKinds::DIAG, ShakeSize size = ShakeSize::MEDIUM, int time = 20);

	void PlayerDeath(int playerNum);	// �v���C���[�̎��S����

	void PlayerLoad(int num);
private:

	std::shared_ptr<Stage>stage_;

	//�v���C���[
	std::shared_ptr<PlayerBase> players_[PLAYER_MAX];

	void ColisionWave(void);	// �����蔻��`�F�b�N

	int aliveCount_;	// �������Ă���v���C���[�̐�

	int timeImg_;
	float limitTime_;

	// �q�b�g�X�g�b�v�J�E���^�[
	static int hitStop_;

	// �X���[�J�E���^�[
	static int slow_;
	static int slowInter_;

	// ��ʗh��------------------------
	int mainScreen_;
	static int shake_;
	static ShakeKinds shakeKinds_;
	static ShakeSize shakeSize_;
	Vector2I ShakePoint(void);
	//---------------------------------
};


using ShakeKinds = GameScene::ShakeKinds;
using ShakeSize = GameScene::ShakeSize;