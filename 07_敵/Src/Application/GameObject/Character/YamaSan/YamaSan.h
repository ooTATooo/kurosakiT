﻿#pragma once

#include "../CharBase.h"

class YamaSan :public CharBase
{
public:

	YamaSan() { Init(); }
	~YamaSan()override {}

	void Update()override;
	void PostUpdate()override;

private:

	void Init();

	float m_gravity = 0;
};