#include "Tank.h"

void Tank::Update()
{
	if (!m_spModel)return;

	Math::Vector3 moveVec;
	bool moveFlg = false;

	if (GetAsyncKeyState('W') & 0x8000)
	{
		moveVec = { 0,0,1 };
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		moveVec = { 0,0,-1 };
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		moveVec = { -1,0,0 };
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		moveVec = { 1,0,0 };
	}
}

void Tank::GenerateDepthMapFromLight()
{
	if (!m_spModel)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel,m_mWorld);
}

void Tank::DrawLit()
{
	if (!m_spModel)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Tank::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/tank/tank.gltf");
	}
}
