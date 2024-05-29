#include "Stage.h"

void Stage::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/SideViewMap/SideViewMap.gltf");

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(0, -2, 0);

	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(5, 1, 1);

	m_mWorld = scaleMat * transMat;

	// 当たり判定用の初期化
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("StageCollision", m_model, KdCollider::TypeGround);

}

void Stage::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
