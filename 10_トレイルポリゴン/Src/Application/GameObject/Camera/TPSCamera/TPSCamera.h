#pragma once
#include "../CameraBase.h"

class TPSCamera : public CameraBase
{
public:

	TPSCamera() { Init(); }
	~TPSCamera()override {}

	void Update()override;

private:

	void Init()override;

	bool m_free = false;
};