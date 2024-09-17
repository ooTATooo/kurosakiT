#include "MyPolygon.h"
#include "../../Scene/SceneManager.h"

void MyPolygon::Init()
{
	m_spPoly = std::make_shared<KdSquarePolygon>();

	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 5, 0);

	Math::Matrix scaleMat = Math::Matrix::CreateScale(5, 5, 1);

	m_mWorld = scaleMat * transMat;
}

void MyPolygon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);
}

void MyPolygon::Update()
{
	m_spPoly->SetMaterial(SceneManager::Instance().GetRenderTargetTexture());
}
