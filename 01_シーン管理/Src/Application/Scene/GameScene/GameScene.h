#pragma once

#include"../BaseScene/BaseScene.h"

class GameScene:public BaseScene
{
public:

	GameScene() { Init(); };
	~GameScene() { Release(); };

	void Update()override;
	void Draw()override;
	void Init()override;
	void Release()override;

private:

	KdTexture m_playerTex;

};