#include "GameScene.h"
#include "../SceneManager.h"

#include "../../Object/Back/Back.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	// プレイヤー座標を取得
	Math::Vector3 playerPos;
	if (!m_player.expired())
	{
		playerPos = m_player.lock()->GetPos();
	}

	// カメラ処理
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(playerPos.x + 3.0f, playerPos.y + 1.5f, playerPos.z + -5.0f);
	//Math::Matrix mat;
	m_camera->SetCameraMatrix(transMat);

	// 被写界深度
	m_camera->SetFocus(5, 2, 3);

	// ブルーム
	KdShaderManager::Instance().m_postProcessShader.SetBrightThreshold(0.7f);

}

void GameScene::Init()
{
	// カメラ
	m_camera = std::make_unique<KdCamera>();

	// 環境設定
	// 平行光(ディレクションライト)										↓距離		↓高さ
	KdShaderManager::Instance().WorkAmbientController().SetDirLight({ 0,-1,0.1f }, { 1,1,1 });

	// フォグ(霧)
	//KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, true);
	//																		↓色			↓密度
	//KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 0.2f,0.0f,0.2f }, 0.05f);

	// 高さフォグ														↓色  ↓上 ↓下 ↓距離
	//KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 1,1,1 }, 0, -2, 0);

	// 環境光(アンビエントライト)
	// 画面が暗すぎる時に調整(デフォルト0.3)
	//KdShaderManager::Instance().WorkAmbientController().SetAmbientLight({ 1,1,1,1 });


	// 1ポインタを作成(このポインタ何も入っていない)
	// まだこの段階で使い物にならない
	std::shared_ptr<Stage> stage;


	for (int i = 0; i < 10; i++)
	{
		// 2領域を確保し、アドレスを1に代入
		// 実体化
		stage = std::make_shared<Stage>();

		stage->SetPos({ 0.f,-2.f,3.f * i });

		// 3実体化した2をオブジェクトリストに格納
		m_objList.push_back(stage);
	}

	for (int i = 0; i < 5; i++)
	{
		// 2領域を確保し、アドレスを1に代入
		// 実体化
		stage = std::make_shared<Stage>();

		stage->SetPos({ 0.f,-2.f + 5 * i,0.f });

		// 3実体化した2をオブジェクトリストに格納
		m_objList.push_back(stage);
	}


	// プレイヤー
	std::shared_ptr<Player> player = std::make_shared<Player>();
	m_objList.push_back(player);
	m_player = player;

	std::shared_ptr<Back> back = std::make_shared<Back>();
	m_objList.push_back(back);

	for (int i = 0; i < 5; i++)
	{
		// 敵
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
		enemy->SetPos({ -25.f + i,0,0 });
		m_objList.push_back(enemy);
	}

}
