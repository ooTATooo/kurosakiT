#include "CharBase.h"

void CharBase::Update()
{
	if (!m_spModel) { return; }
}

void CharBase::PostUpdate()
{
	if (!m_spModel) { return; }

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;
}

void CharBase::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();

		m_pCollider = std::make_unique<KdCollider>();
	}
}

void CharBase::DrawLit()
{
	if (!m_spModel) { return; }

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
