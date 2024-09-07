#include "Tank.h"

#include "../../main.h"
#include "../Camera/CameraBase.h"
#include "../../Scene/SceneManager.h"
#include "../Bullet/Bullet.h"

void Tank::Update()
{
	if (!m_spModel)return;

	// カメラのY回転行列を取得
	Math::Matrix camRotYMat;
	std::shared_ptr<CameraBase> camera = m_wpCamera.lock();
	if (camera)
	{
		camRotYMat = camera->GetRotationYMatrix();
	}

	Math::Vector3 moveVec;	// 向きたい方向(進みたい方向)
	bool moveFlg = false;	// 状態フラグ(移動中)

	if (GetAsyncKeyState('W') & 0x8000)
	{
		moveVec += Math::Vector3::TransformNormal({ 0, 0, 1 }, camRotYMat);
		moveFlg = true;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		moveVec += Math::Vector3::TransformNormal({ 0, 0, -1 }, camRotYMat);
		moveFlg = true;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		moveVec += Math::Vector3::TransformNormal({ -1, 0, 0 }, camRotYMat);
		moveFlg = true;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		moveVec += Math::Vector3::TransformNormal({ 1, 0, 0 }, camRotYMat);
		moveFlg = true;
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>();
		Math::Vector3 pos = m_pos;
		pos.y += 2.0f;

		Math::Vector3 dir;

		if (m_tpsFlg)
		{
			Math::Vector3 camPos;
			float range = 0;

			// カメラ情報を取得
			//if (camera)
			//{
			//	camPos = camera->GetPos();
			//	// レイ判定をするにあたってのRayInfoを生成
			//	camera->WorkCamera()->GenerateRayInfoFromClientPos({ 640,360 }, camPos, dir, range);
			//}
			if (m_wpCamera.expired() == false)
			{
				camPos = m_wpCamera.lock()->GetPos();

				// レイ判定をするにあたってのRayInfoを生成
				m_wpCamera.lock()->WorkCamera()->GenerateRayInfoFromClientPos({ 640,360 }, camPos, dir, range);
			}

			// レイ判定
			KdCollider::RayInfo ray;
			ray.m_pos = camPos;
			ray.m_dir = dir;
			ray.m_range = range;
			ray.m_type = KdCollider::TypeGround | KdCollider::TypeDamage;

			// 当たり判定
			float overlap = 0;
			std::list<KdCollider::CollisionResult> rayRetList;
			for (auto& obj : SceneManager::Instance().GetObjList())
			{
				obj->Intersects(ray, &rayRetList);
			}

			// 一番近くであたったものを検出
			Math::Vector3 hitPos;
			for (auto& ret : rayRetList)
			{
				if (overlap < ret.m_overlapDistance)
				{
					// 更新
					overlap = ret.m_overlapDistance;
					hitPos = ret.m_hitPos;
					// 一番近くで当たったものへの方向ベクトルを算出
					dir = hitPos - pos;
					dir.Normalize();
				}
			}
		}
		else
		{
			dir = m_mWorld.Backward();
		}

		bullet->SetParam(pos, dir);

		SceneManager::Instance().AddObject(bullet);
	}

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		m_tpsFlg = true;
	}
	else
	{
		m_tpsFlg = false;
	}

	Math::Matrix rotMat;
	if (m_tpsFlg)
	{
		// TPS
		moveVec.Normalize();

		// 回転
		rotMat = camRotYMat;

		if (camera)
		{
			camera->SetCameraPos({ 2.0f,3.0f, -5.0f });
		}
	}
	else
	{
		// TPV
		if (camera)
		{
			camera->SetCameraPos({ 0, 4.5f, -10.0f });
		}

		m_atkFlg = false;
		if (moveFlg)
		{
			// 攻撃中
			m_atkFlg = true;

			// 移動中
			// 回転処理

			// 今戦車が向いている方向
			// キャラの回転行列を作成
			Math::Matrix nowRotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

			// 現在の方向を求める
			Math::Vector3 nowVec = Math::Vector3::TransformNormal({ 0,0,1 }, nowRotMat);

			// もう一つ
			//Math::Vector3 nowVec = m_mWorld.Backward();

			// 向きたい方向
			Math::Vector3 toVec = moveVec;

			// 方向をベクトルで管理する場合、ベクトルの長さは1にする
			toVec.Normalize();

			// 内積…ベクトルAとベクトルBとコサインなす角
			// ベクトルA*ベクトルB*コサインなす角
			//     1    *    1    *コサインなす角
			// = コサインなす角
			// A・B
			float d = nowVec.Dot(toVec);

			// 丸め誤差…小数点以下を省略した際に生じる誤差
			// 内積は-1～1が出る
			// -1～1でdの値をクランプ(遮断)する
			d = std::clamp(d, -1.0f, 1.0f);

			// アークコサインで角度に変換
			float ang = DirectX::XMConvertToDegrees(acos(d));

			// ゆっくり回転する処理
			if (ang >= 0.1f)
			{
				// とりあえず最大で5度回転するように制御
				if (ang > 5)
				{
					ang = 5.0f;
				}

				// 外積…ベクトルAとベクトルBに垂直なベクトル
				// A×B
				Math::Vector3 c = toVec.Cross(nowVec);

				if (c.y >= 0)
				{
					m_angle -= ang;
					if (m_angle < 0)
					{
						m_angle += 360;
					}
				}
				else
				{
					m_angle += ang;
					if (m_angle >= 360)
					{
						m_angle -= 360;
					}
				}
			}

			rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
		}
	}

	// printf
	//Application::Instance().m_log.AddLog("m_angle=%.2f ang=%.2f\n", m_angle, ang);

	m_pos += moveVec * 0.1f;
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = rotMat * transMat;
}

void Tank::PostUpdate()
{
	if (!m_atkFlg) { return; }

	// 当たり判定(スフィア)
	KdCollider::SphereInfo atkSphere;
	atkSphere.m_sphere.Center = m_pos;
	atkSphere.m_sphere.Center.y += 0.5;
	atkSphere.m_sphere.Radius = 2;
	atkSphere.m_type = KdCollider::TypeDamage;

	m_pDebugWire->AddDebugSphere(atkSphere.m_sphere.Center, atkSphere.m_sphere.Radius);

	// 全オブジェトとの当たり判定
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(atkSphere, nullptr))
		{
			// 当たった
			obj->OnHit();
		}
	}
}

void Tank::GenerateDepthMapFromLight()
{
	if (!m_spModel)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Tank::DrawLit()
{
	if (!m_spModel)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Tank::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/tank/tank.gltf");
	}

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

}
