#include <DxLib.h>
#include <vector>
#include <functional>
#include <memory>
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

	static constexpr float JUMP_MAX = 100.0f;	//�W�����v�̍ō����B�_
	static constexpr float JUMP_ROAL = 0.5f;	//��]�̍d������
	static constexpr float JUMP_DURABILITY = 1.0f;	//�󒆑؍݊���(�ʏ펞)

	static constexpr float INVINCIBLE_TIME = 1.0f;	//���G����(�_���[�W��)

	static constexpr int MAX_HP = 3;

	PlayerBase(int playerNum , VECTOR pos);
	virtual ~PlayerBase(void);
	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);

	const int GetHp(void) { return hp_; }
	void Damage(void);
protected:
	int modelId_;
	VECTOR pos_;
	VECTOR initPos_;
	int playerNum_;
	int color_;
	STATE state_;
	std::vector<std::shared_ptr<Wave>>waves;
	float jumpTime_;
	int hp_;

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