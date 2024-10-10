#include "Ground.h"

void Ground::GenerateDepthMapFromLight()
{
	if (!m_spModel)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Ground::DrawLit()
{
	if (!m_spModel)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);

	Math::Matrix Rotmat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(90));
	Math::Matrix scaleMat = Math::Matrix::CreateScale(100.0f);
	Math::Matrix mat = scaleMat * Rotmat;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, mat);
}

void Ground::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/Ground/Ground.gltf");

		Math::Matrix scaleMat = Math::Matrix::CreateScale(100.0f);

		m_mWorld = scaleMat;
	}
}
