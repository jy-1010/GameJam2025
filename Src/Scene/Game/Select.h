#pragma once
#include"../SceneBase.h"

class Select : public SceneBase
{
public:
	Select();
	~Select();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:
	int backImg_;
	int img_[4];
	int selectNum_;
};

