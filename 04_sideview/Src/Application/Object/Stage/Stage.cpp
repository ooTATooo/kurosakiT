#include "Stage.h"

void Stage::Init()
{
	m_model.Load("Asset/Models/SideViewMap/SideViewMap.gltf");

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(0, -2, 0);

	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(5, 1, 1);

	m_mWorld = scaleMat * transMat;
}

void Stage::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model,m_mWorld);
}
