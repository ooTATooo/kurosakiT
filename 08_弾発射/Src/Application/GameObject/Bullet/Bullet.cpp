#include "Bullet.h"

void Bullet::Update()
{
	m_pos += m_dir * m_speed;

	m_lifeSpan--;
	if (m_lifeSpan < 0)
	{
		m_isExpired - true;
	}

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;
}

void Bullet::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/Bullet/Bullet.gltf");
	}
}

void Bullet::DrawLit()
{
	if (!m_spModel) { return; }

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Bullet::DrawBright()
{
	if (!m_spModel) { return; }

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Bullet::SetParam(Math::Vector3 _pos, Math::Vector3 _dir, float _speed, int _lifeSpan)
{
	m_pos = _pos;
	m_dir = _dir;
	m_speed = _speed;
	m_lifeSpan = _lifeSpan;
}
