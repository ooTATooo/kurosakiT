#include "GameScene.h"
#include "../SceneManager.h"

#include "../../Object/Back/Back.h"
#include "../../Object/Stage/Stage.h"
#include "../../Object/Player/Player.h"

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
}

void GameScene::Init()
{
	// カメラ
	m_camera = std::make_unique<KdCamera>();

	// 1ポインタを作成(このポインタ何も入っていない)
	// まだこの段階で使い物にならない
	std::shared_ptr<Stage> stage;

	// 2領域を確保し、アドレスを1に代入
	// 実体化
	stage = std::make_shared<Stage>();

	// 3実体化した2をオブジェクトリストに格納
	m_objList.push_back(stage);

	// プレイヤー
	std::shared_ptr<Player> player = std::make_shared<Player>();
	m_objList.push_back(player);
	m_player = player;

	std::shared_ptr<Back> back = std::make_shared<Back>();
	m_objList.push_back(back);
}
