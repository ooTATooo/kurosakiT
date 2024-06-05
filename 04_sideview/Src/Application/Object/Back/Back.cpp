#include "Back.h"

void Back::Init()
{
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/back.png");
	Math::Matrix transeMat = Math::Matrix::CreateTranslation(0, 0, 50);
	Math::Matrix scaleMat = Math::Matrix::CreateScale(300, 100, 1);
	m_mWorld = scaleMat * transeMat;
}

void Back::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}
