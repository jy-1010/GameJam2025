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
		LAND,	//地上にいる状態
		JUMP,	//ジャンプ
		ROAL,	//回転状態
		DROP,	//回転後落下状態
		DAMAGE,	//ダメージ後無敵処理
		DEATH,	//死亡
		MAX
	};

	static constexpr float JUMP_MAX = 100.0f;	//ジャンプの最高到達点
	static constexpr float JUMP_ROAL = 0.5f;	//回転の硬直時間
	static constexpr float JUMP_DURABILITY = 1.0f;	//空中滞在期間(通常時)

	static constexpr float INVINCIBLE_TIME = 1.0f;	//無敵時間(ダメージ後)

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