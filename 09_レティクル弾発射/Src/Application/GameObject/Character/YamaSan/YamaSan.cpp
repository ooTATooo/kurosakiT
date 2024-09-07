#include "YamaSan.h"

void YamaSan::Update()
{
	CharBase::Update();

	Math::Vector3 moveVec;
	const std::shared_ptr<const KdGameObject> target = m_target.lock();
	if (target)
	{
		// 敵から見たターゲットの方向を算出
		// ゴール - スタートでスタートからゴールのベクトル
		moveVec = target->GetPos() - m_pos;
	}

	m_pos.y -= m_gravity;
	m_gravity += 0.01f;
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
		m_gravity = -0.3f;
	}

	// 長さ1にする
	moveVec.Normalize();
	m_pos += moveVec * 0.05f;
}

void YamaSan::PostUpdate()
{
	CharBase::PostUpdate();
}

void YamaSan::Init()
{
	CharBase::Init();

	m_spModel->Load("Asset/Models/Enemy/Yama/yama.gltf");

	m_gravity = 0.1f;

	m_pCollider->RegisterCollisionShape("MotoSan", m_spModel, KdCollider::TypeDamage);

}
