#include <DxLib.h>
#include <vector>
#include <functional>
#include <memory>
#include <map>
#include "../Wave.h"

class PlayerBase
{
public:
	
	enum class STATE
	{
		LAND,	//�n��ɂ�����
		JUMP,	//�W�����v
		ROAL,	//��]���
		DROP,	//��]�㗎�����
		DAMAGE,	//�_���[�W�㖳�G����
		DEATH,	//���S
		MAX
	};

	//static constexpr float JUMP_MAX = 100.0f;	//�W�����v�̍ō����B�_
	static constexpr float JUMP_ROAL = 30.0f;	//��]�̍d������(�t���[����)
	static constexpr float JUMP_DURABILITY = 60.0f;	//�󒆑؍݊���(�ʏ펞)(�t���[��

	static constexpr float INVINCIBLE_TIME = 60.0f;	//���G����(�_���[�W��)(�t���[��

	static constexpr float JUMP_SPEED = 50.0f;	//�W�����v�̏㏸���x
	static constexpr float JUMP_DECELERATION = JUMP_SPEED / (JUMP_DURABILITY / 2);	//�W�����v�̌�����

	static constexpr float JUMP_DROP_SPEED = 20.0f;	//�������x

	static constexpr int MAX_HP = 3;

	static constexpr float RADIUS = 20.0f;	//�v���C���[�̔��a

	PlayerBase(int playerNum , VECTOR pos);
	virtual ~PlayerBase(void);
	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);

	const int GetHp(void) { return hp_; }
	bool IsLand(void) { return state_ == STATE::LAND; }
	bool IsDeath(void) { return state_ == STATE::DEATH; }
	void Damage(void);

	VECTOR GetInitPos(void) const { return initPos_; }
	std::vector<float> GetWaveRadius(void) const;

protected:
	int modelId_;
	VECTOR pos_;
	VECTOR rot_;
	VECTOR initPos_;
	int playerNum_;
	int color_;
	STATE state_;
	std::vector<std::shared_ptr<Wave>>waves;
	float rotFlame_;
	float invincibleTime_;	//���G����(�_���[�W��)(�t���[����)
	int hp_;
	Wave::SPEED_TYPE waveSpeedType_;

	float deceleration_;	//������

	std::map<STATE, std::function<void(void)>> stateChanges_;
	std::function<void(void)> stateUpdate_;

	virtual void UpdateLand(void);
	virtual void UpdateJump(void);
	virtual void UpdateRoal(void);
	virtual void UpdateDrop(void);
	virtual void UpdateDamage(void);
	virtual void UpdateDeath(void);
	virtual void ChengeState(STATE state);

	virtual void ChengeStateLand(void);
	virtual void ChengeStateJump(void);
	virtual void ChengeStateRoal(void);
	virtual void ChengeStateDrop(void);
	virtual void ChengeStateDamage(void);
	virtual void ChengeStateDeath(void);

	void MakeWave(Wave::SPEED_TYPE speedType);
private:
};