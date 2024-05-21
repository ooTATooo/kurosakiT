#include "GameScene.h"

void GameScene::Update()
{
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
