#include "SceneManager.h"
#include"BaseScene/BaseScene.h"
#include"TitleScene/TitleScene.h"
#include"GameScene/GameScene.h"
void SceneManager::Update()
{
	m_currentScene->Update();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::Init()
{
	ChangeScene(m_currentSceneType);
}

void SceneManager::Release()
{
	m_currentScene->Release();
}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	// 次のシーンを作成して、現在のシーンにする
	switch (_sceneType)
	{
	case SceneManager::SceneType::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneManager::SceneType::Game:
		m_currentScene = std::make_shared<GameScene>();
		break;
	default:
		break;
	}

	// シーン管理を更新
	m_currentSceneType = _sceneType;
}
