#pragma once
#include <DxLib.h>
class Wave
{
public:
	enum class SPEED_TYPE
	{
		SLOW,
		MIDIUM,
		FAST,
		MAX,
	};

	static constexpr float SLOW_SPEED = 500;
	static constexpr float MIDIUM_SPEED = 700;
	static constexpr float FAST_SPEED = 1000;
	static constexpr int VERTEX_NUM = 180;

	static constexpr float MAX_RADIUS = 2500.0f;	//�g��̍ő唼�a

	Wave(VECTOR centerPos,SPEED_TYPE speedType , int color );
	~Wave();
	void Init(void);
	void Update(void);
	void Draw(void);
	void Reset(void);

	float GetRadius(void) const { return speed_ * time_; }

	bool IsEnd(void) const { return MAX_RADIUS <= speed_ * time_; }
private:
	int color_;
	float speed_;
	VECTOR centerPos_;
	float time_;

	float InitSpeed(SPEED_TYPE speedType) const;

};

