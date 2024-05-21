#pragma once

// 基底クラス(親クラス)
class BaseScene
{
public:

	BaseScene() {}
	~BaseScene() {}

	// 各シーンに共通する仮想関数
	virtual void Update();
	virtual void Draw();
	virtual void Init();
	virtual void Release();

protected:



private:



};