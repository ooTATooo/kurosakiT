#include "MotoSan.h"

void MotoSan::Update()
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

	// 長さ1にする
	moveVec.Normalize();
	m_pos += moveVec * 0.06f;
}

void MotoSan::PostUpdate()
{
	CharBase::PostUpdate();
}

void MotoSan::Init()
{
	CharBase::Init();

	m_spModel->Load("Asset/Models/Enemy/Moto/moto.gltf");

	m_pCollider->RegisterCollisionShape("MotoSan", m_spModel, KdCollider::TypeDamage);
}
