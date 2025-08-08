#include <DxLib.h>
#include <vector>
#include <functional>
#include <memory>
#include <map>
#include "../Wave.h"
#include"../../Manager/AnimationController/AnimationController.h"

class LifeUI;
class GameScene;

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

	static constexpr float DAMAGE_DELAY = 30.0f;	//ダメージ後の硬直時間(フレーム数)//
	static constexpr float INVINCIBLE_TIME = 60.0f;	//無敵時間(ダメージ後)(フレーム

	static constexpr float JUMP_SPEED = 50.0f;	//ジャンプの上昇速度
	static constexpr float JUMP_DECELERATION = JUMP_SPEED / (JUMP_DURABILITY / 2);	//ジャンプの減速率

	static constexpr float JUMP_DROP_SPEED = 40.0f;	//落下速度

	static constexpr int MAX_HP = 3;

	static constexpr float RADIUS = 50.0f;	//プレイヤーの半径

	//アニメーション種別
	enum class ANIM_TYPE
	{
		DEATH,
		DUCK,
		HIT_REACT,
		IDLE,
		IDLE_ATTACK,
		IDLE_HOLD,
		JUMP,
		JUMP_IDLE,
		JUMP_LAND,
		NO,
		PUNCH,
		RUN,
		RUN_ATTACK,
		RUN_HOLD,
		WALK,
		WALK_HOLD,
		WAVE,
		YES,
		MAX,
		DANCE1,
	};

	PlayerBase(GameScene& gameScene,int playerNum , VECTOR pos);
	virtual ~PlayerBase(void);
	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);

	const int GetHp(void) { return hp_; }
	bool IsLand(void) { return state_ == STATE::LAND; }
	bool IsDeath(void) { return state_ == STATE::DEATH; }
	virtual void Damage(VECTOR vec);

	VECTOR GetInitPos(void) const { return initPos_; }
	std::vector<float> GetWaveRadius(void) const;

protected:

	static constexpr float DEATH_MOVE_SPEED_XZ = 20.0f;	//死亡時の移動速度
	static constexpr float DEATH_MOVE_SPEED_Y = 10.0f;	//死亡時の移動速度

	GameScene& gameScene_;	//ゲームシーン

	int modelId_;
	VECTOR pos_;
	VECTOR rot_;
	VECTOR scale_;
	VECTOR initPos_;
	VECTOR deathVec_;	//死亡時のベクトル(ダメージを受けた方向)
	int playerNum_;
	int color_;
	STATE state_;
	std::vector<std::shared_ptr<Wave>>waves;
	float rotFlame_;
	float invincibleTime_;	//無敵時間(ダメージ後)(フレーム数)
	int hp_;
	Wave::SPEED_TYPE waveSpeedType_;

	std::shared_ptr<LifeUI> lifeUI_;	//ライフUI

	float deceleration_;	//減速率

	bool isInvincible_;	//無敵状態かどうか

	std::shared_ptr<AnimationController>anime_;

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