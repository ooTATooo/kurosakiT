#include "Player.h"

void Player::Update()
{
	m_poly.SetUVRect(8);
}

void Player::Init()
{
	m_poly.SetMaterial("Asset/Textures/char.png");
	m_poly.SetSplit(6, 6);
	m_pos = {};
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_poly);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_poly);
}
