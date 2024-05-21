#pragma once

// 継承時限定で include OK
#include"../BaseScene/BaseScene.h"

class TitleScene :public BaseScene
{
public:

	//実体化したら一番最初に一度だけ動く関数
	TitleScene() { Init(); };
	//消去時に一度だけ動く関数
	~TitleScene() { Release(); };

	//関数
	void Update()override;
	void Draw()override;
	void Init()override;
	void Release()override;
	// override
	// 基底(親)クラスと同じ関数を派生(子)クラスで上書き

private:

	//変数
	KdTexture m_titleTex;
	KdTexture m_startTex;

	float m_alpha = 1.0f;
	float m_alphaAdd = 0.01f;


};