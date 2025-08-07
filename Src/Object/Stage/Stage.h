#pragma once

#include<vector>

class Stage
{
public:
	enum class BLOCK {
		NON=-1,


		MAX
	};

	Stage();
	~Stage();

	void Load(void);
	void Draw(void);
	void Release(void);

private:
	std::vector<int>blocks_;
	std::vector<std::vector<int>>mapData_;
};

