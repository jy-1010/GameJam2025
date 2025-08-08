#pragma once
#include"../SceneBase.h"

class Finish : public SceneBase
{
public:
	Finish();
	~Finish();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:
	int img_;
	float scale_;
};
