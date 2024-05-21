#include "GameScene.h"

#include"../SceneManager.h"

void GameScene::Update()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::instance().SetNextScene(SceneManager::SceneType::Title);
	}
}

void GameScene::Draw()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_playerTex, 0, 0);
}

void GameScene::Init()
{
	m_playerTex.Load("Asset/Textures/player.png");
}

void GameScene::Release()
{
	m_playerTex.Release();
}
