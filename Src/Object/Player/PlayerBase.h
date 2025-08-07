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
		LAND,	//地上にいる状態
		JUMP,	//ジャンプ
		ROAL,	//回転状態
		DROP,	//回転後落下状態
		DAMAGE,	//ダメージ後無敵処理
		DEATH,	//死亡
		MAX
	};

	//static constexpr float JUMP_MAX = 100.0f;	//ジャンプの最高到達点
	static constexpr float JUMP_ROAL = 30.0f;	//回転の硬直時間(フレーム数)
	static constexpr float JUMP_DURABILITY = 60.0f;	//空中滞在期間(通常時)(フレーム

	static constexpr float INVINCIBLE_TIME = 60.0f;	//無敵時間(ダメージ後)(フレーム

	static constexpr float JUMP_SPEED = 50.0f;	//ジャンプの上昇速度
	static constexpr float JUMP_DECELERATION = JUMP_SPEED / (JUMP_DURABILITY / 2);	//ジャンプの減速率

	static constexpr float JUMP_DROP_SPEED = 20.0f;	//落下速度

	static constexpr int MAX_HP = 3;

	static constexpr float RADIUS = 20.0f;	//プレイヤーの半径

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
	float invincibleTime_;	//無敵時間(ダメージ後)(フレーム数)
	int hp_;
	Wave::SPEED_TYPE waveSpeedType_;

	float deceleration_;	//減速率

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