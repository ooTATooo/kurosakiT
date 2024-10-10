#include "Tank.h"

#include "../../main.h"
#include "../Camera/CameraBase.h"

void Tank::Update()
{
	if (!m_spModel)return;

	// 黒崎授業
	// カラースフィア
	KdShaderManager::Instance().WriteCBColor({ 0,0,0 }, 10, { 0,0,1 });

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

	if (moveFlg)
	{
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

		// printf
		Application::Instance().m_log.AddLog("m_angle=%.2f ang=%.2f\n", m_angle, ang);

		Math::Matrix rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

		m_pos += moveVec * 0.1f;
		Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

		m_mWorld = rotMat * transMat;
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

	// 黒崎授業
	KdShaderManager::Instance().WriteCBColorEnable(false);

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);

	KdShaderManager::Instance().WriteCBColorEnable(true);
}

void Tank::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelData>();
		m_spModel->Load("Asset/Models/tank/tank.gltf");
	}
}
