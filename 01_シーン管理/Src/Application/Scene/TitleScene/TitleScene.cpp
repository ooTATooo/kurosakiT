#include "TitleScene.h"

void TitleScene::Update()
{
	// m_alphaを増やしたり減らしたりする処理
	// m_alphaは0～1で推移するように
	m_alpha += m_alphaAdd;
	if (m_alpha > 1)
	{
		m_alpha = 1.0f;
		m_alphaAdd *= -1;
	}
	if (m_alpha < 0.3)
	{
		m_alpha = 0.3f;
		m_alphaAdd *= -1;
	}
}

void TitleScene::Draw()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_titleTex, 0, 0);
	Math::Color color = { 1,1,1,m_alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_startTex, 0, -200, nullptr, &color);
}

void TitleScene::Init()
{
	// タイトルテクスチャ読み込み
	m_titleTex.Load("Asset/Textures/title.png");
	m_startTex.Load("Asset/Textures/start.png");
}

void TitleScene::Release()
{
	m_titleTex.Release();
	m_startTex.Release();
}

