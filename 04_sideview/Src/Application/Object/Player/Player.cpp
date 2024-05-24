#include "Player.h"

void Player::Update()
{

	// アニメーション
	int run[4] = { 24,25,24,26 };
	int atk[3] = { 6,7,8 };
	m_poly.SetUVRect(run[(int)m_anime]);

	m_anime += 0.1f;
	if (m_anime >= 4)
	{
		m_anime = 0;
	}

	// 移動処理
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { m_pos.x -= 0.1f; }
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_pos.x += 0.1f; }

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Player::Init()
{
	m_poly.SetMaterial("Asset/Textures/char.png");
	m_poly.SetSplit(6, 6);
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_poly, m_mWorld);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_poly, m_mWorld);
}
