#include "Bullet.h"

#include "../../Scene/SceneManager.h"

void Bullet::Update()
{
	m_pos += m_dir * m_speed;

	m_lifeSpan--;
	if (m_lifeSpan < 0)
	{
		m_isExpired = true;
	}

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;

	// スコープを切る
	{
		// トレイルポリゴンに頂点を追加
		m_tPoly.AddPoint(m_mWorld);
	}
}

void Bullet::PostUpdate()
{
	// 早期リターン
	if (m_isExpired)return;

	// 当たり判定
	KdCollider::SphereInfo sphere;
	sphere.m_sphere.Center = m_pos;
	sphere.m_sphere.Radius = 0.5f;
	sphere.m_type = KdCollider::TypeGround | KdCollider::TypeDamage;


	std::list<KdCollider::CollisionResult> retList;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(sphere, &retList);
	}

	float overLap = 0;
	bool hit = false;
	Math::Vector3 normal;
	for (auto& ret : retList)
	{
		if (overLap < ret.m_overlapDistance)
		{
			// 更新
			hit = true;
			normal = ret.m_hitNormal;
			overLap = ret.m_overlapDistance;
		}
	}
	// このfor文を抜けてら一番近くであたっためんの情報が取得できる

	if (hit)
	{
		// 反射ベクトル
		float a = -m_dir.Dot(normal);
		Math::Vector3 r = m_dir + 2 * a * normal;
		r.Normalize();

		m_dir = r;
	}

}

void Bullet::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/Bullet/Bullet.gltf");

	}

	//m_tPoly.SetLength(200);
	m_tPoly.SetMaterial("Asset/Textures/jet.png");
}

void Bullet::DrawLit()
{
	if (!m_spModel) { return; }

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_tPoly);

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
