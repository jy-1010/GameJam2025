#pragma once
#include <DxLib.h>
class Wave
{
public:
	enum class SPEED_TYPE
	{
		SLOW =100,
		MIDIUM = 200,
		FAST = 1000,

	};

	//static constexpr float SLOW_SPEED = 100;
	//static constexpr float MIDIUM_SPEED = 200;
	//static constexpr float SLOW_SPEED = 300;
	static constexpr int VERTEX_NUM = 180;

	Wave(VECTOR centerPos,SPEED_TYPE speedType , int color );
	~Wave();
	void Init(void);
	void Update(void);
	void Draw(void);
	void Reset(void);
private:
	int color_;
	float speed_;
	VECTOR centerPos_;
	float time_;
};

