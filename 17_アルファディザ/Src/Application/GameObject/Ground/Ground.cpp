#include "Ground.h"

void Ground::DrawLit()
{
	if (!m_spModel)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel_obj, Math::Matrix::Identity);
}

void Ground::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/Ground/Ground.gltf");

		m_spModel_obj = std::make_shared<KdModelData>();
		m_spModel_obj->Load("Asset/Models/map/map.gltf");

		Math::Matrix scaleMat = Math::Matrix::CreateScale(100.0f);

		m_mWorld = scaleMat;
	}
}
