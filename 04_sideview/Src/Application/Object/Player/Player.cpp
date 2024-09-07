#include "Player.h"

#include "../../Scene/SceneManager.h"

void Player::Update()
{
	// アニメーション
	int run[4] = { 24,25,24,26 };
	int atk[3] = { 6,7,8 };
	m_poly.SetUVRect(run[(int)m_anime]);
	//m_poly.SetUVRect(32);

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

	//==========================
	// 球判定
	//==========================

	// 球判定用の変数を作成
	KdCollider::SphereInfo sphere;
	// 球の中心点を設定
	sphere.m_sphere.Center = m_pos;
	sphere.m_sphere.Center.y += 0.5f;
	// 球の半径を設定
	sphere.m_sphere.Radius = 0.3f;
	// 当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeGround;

	// デバッグ表示
	Math::Color color = { 1,1,0,1 };
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, color);

	// 球に当たったオブジェクトの情報を格納
	std::list<KdCollider::CollisionResult> retSphereList;

	// 当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(sphere, &retSphereList);
	}

	// 球に当たったオブジェクトを検出
	maxOverLap = 0;	// はみでたレイの長さ
	Math::Vector3 hitDir;	// 当たった方向
	isHit = false;		// 当たっていたらtrue
	for (auto& ret : retSphereList)
	{
		// 球にめりこんで、オーバーした長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			isHit = true;
		}
	}

	if (isHit)
	{
		// Y.Z方向への押し返し無効
		hitDir.y = 0;
		hitDir.z = 0;
		// 正規化(長さを１にする)
		// 方向は絶対長さ１
		hitDir.Normalize();

		// 地面に当たっている
		m_pos += hitDir * maxOverLap;
	}


	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Player::Init()
{
	m_poly.SetMaterial("Asset/Textures/char.png");

	// 画像分割
	m_poly.SetSplit(6, 6);
	// 原点変更
	m_poly.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_pos = { -54,0,0 };

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_poly, m_mWorld);
}

void Player::DrawLit()
{
	// ディゾルブ(溶ける)
	static float d = 0;
	d += 0.01f;
	if (d > 1)
	{
		d = 0;
	}
	KdShaderManager::Instance().m_StandardShader.SetDissolve(d);


	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_poly, m_mWorld);
}
