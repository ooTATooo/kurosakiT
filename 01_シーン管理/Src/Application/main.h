﻿#pragma once

//ヘッダー内でincludeさせない
//ヘッダー内include禁止!!
//#include"Scene/TitleScene/TitleScene.h"

//前方宣言
class TitleScene;
class GameScene;
class BaseScene;

//============================================================
// アプリケーションクラス
//	APP.～ でどこからでもアクセス可能
//============================================================
class Application
{
// メンバ
public:

	// アプリケーション実行
	void Execute();

	// アプリケーション終了
	void End() { m_endFlag = true; }

	HWND GetWindowHandle() const { return m_window.GetWndHandle(); }
	int GetMouseWheelValue() const { return m_window.GetMouseWheelVal(); }

	int GetNowFPS() const { return m_fpsController.m_nowfps; }
	int GetMaxFPS() const { return m_fpsController.m_maxFps; }

private:

	void KdBeginUpdate();
	void PreUpdate();
	void Update();
	void PostUpdate();
	void KdPostUpdate();

	void KdBeginDraw(bool usePostProcess = true);
	void PreDraw();
	void Draw();
	void PostDraw();
	void DrawSprite();
	void KdPostDraw();

	// アプリケーション初期化
	bool Init(int w, int h);

	// アプリケーション解放
	void Release();

	// ゲームウィンドウクラス
	KdWindow		m_window;

	// FPSコントローラー
	KdFPSController	m_fpsController;

	// ゲーム終了フラグ trueで終了する
	bool		m_endFlag = false;

	//これは実体化していない(コンストラクタが動く)
	//生ポインタ(使用禁止)
	//TitleScene* m_nowScene;
	//スマートポインタ
	//std::shared_ptr<BaseScene> m_nowScene;



//=====================================================
// シングルトンパターン
//=====================================================
private:
	//
	Application() {}

public:
	static Application &Instance(){
		static Application Instance;
		return Instance;
	}
};
