#include "Player.h"

#include "../../Scene/SceneManager.h"

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

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) { m_gravity = -0.1f; }
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Player::PostUpdate()
{
	//==========================
	// レイ判定
	//==========================

	// レイ判定用に変数を作成
	KdCollider::RayInfo ray;

	// レイの発射位置(座標)を設定
	ray.m_pos = m_pos;

	// レイの発射方向
	ray.m_dir = Math::Vector3::Down;

	// 少し高いところから飛ばす
	ray.m_pos.y += 0.1f;

	// 段差の許容範囲を設定
	float enableStepHigh = 0.2f;
	ray.m_pos.y += enableStepHigh;

	// レイの長さを設定
	ray.m_range = m_gravity + enableStepHigh;

	// 当たり判定をしたいタイプを設定
	ray.m_type = KdCollider::TypeGround;

	// デバッグ用
	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

	// レイに当たったオブジェクト情報を格納
	std::list<KdCollider::CollisionResult> retrayList;

	// 当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(ray, &retrayList);
	}

	// レイに当たったリストから一番近いオブジェクトを検出
	float maxOverLap = 0;
	Math::Vector3 hitPos;
	bool isHit = false;

	for (auto& ret : retrayList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			isHit = true;
		}
	}

	if (isHit)
	{
		// 一番近くの地面に当たっている
		m_pos = hitPos + Math::Vector3(0, -0.1f, 0);
		m_gravity = 0;
	}
}

void Player::Init()
{
	m_poly.SetMaterial("Asset/Textures/char.png");

	// 画像分割
	m_poly.SetSplit(6, 6);
	// 原点変更
	m_poly.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_poly, m_mWorld);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_poly, m_mWorld);
}
