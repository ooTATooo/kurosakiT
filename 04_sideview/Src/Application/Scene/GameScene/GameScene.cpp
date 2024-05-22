#include "GameScene.h"
#include "../SceneManager.h"

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

	// カメラ
	static float x = 0;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		x -= 0.1f;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		x += 0.1f;
	}

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(x, 2, -5);
	Math::Matrix mat;
	m_camera->SetCameraMatrix(transMat);
}

void GameScene::Init()
{
	// カメラ
	m_camera = std::make_unique<KdCamera>();

	// 1ポインタを作成(このポインタ何も入っていない)
	// まだこの段階で使い物にならない
	std::shared_ptr<Stage> stage = std::make_shared<Stage>();

	// 2領域を確保し、アドレスを1に代入
	// 実体化
	stage = std::make_shared<Stage>();

	// 3実体化した2をオブジェクトリストに格納
	m_objList.push_back(stage);

	// プレイヤー
	std::shared_ptr<Player> player = std::make_shared<Player>();
	m_objList.push_back(player);
}
