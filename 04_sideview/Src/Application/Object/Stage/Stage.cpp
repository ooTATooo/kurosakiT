#include "Stage.h"

void Stage::Init()
{
	m_model.Load("Asset/Models/SideViewMap/SideViewMap.gltf");

	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(5, 1, 1);

	m_mWorld = scaleMat;

}

void Stage::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(m_model,m_mWorld);
}
