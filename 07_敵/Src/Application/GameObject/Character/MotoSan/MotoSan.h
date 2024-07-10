#pragma once

#include "../CharBase.h"

class MotoSan :public CharBase
{
public:

	MotoSan() { Init(); }
	~MotoSan()override {}

	void Update()override;
	void PostUpdate()override;

private:

	void Init();
};