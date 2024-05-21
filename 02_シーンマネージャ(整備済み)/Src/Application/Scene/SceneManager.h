#pragma once

class BaseScene;

class SceneManager
{
public:

	enum class SceneType
	{
		Title,
		Game,
	};

	void PreUpdate();
	void Update();
	void Draw();

	// セッター...メンバー変数の値を変更する関数
	// 本来メンバー変数は外から触れない
	// でもどうしても値をへんこうしたいときに使う
	void SetNextScene(SceneType _nextScene) { m_nextSceneType = _nextScene; }

	// ゲッター
	SceneType GetCurrentScene() { return m_currentSceneType; }

private:

	void Init();
	void Release();

	// 現在のシーンを管理しているポインタ
	std::shared_ptr<BaseScene> m_currentScene = nullptr;
	// 現在のシーンを管理している変数
	SceneType m_currentSceneType = SceneType::Title;
	// 次のシーンを管理している変数
	SceneType m_nextSceneType = m_currentSceneType;

	// シーンを切り替える
	void ChangeScene(SceneType _sceneType);

// シングルトンパターン
// そのクラスのインスタンスが1つしか生成されないことを保証するデザインパターン
private:

	SceneManager() { Init(); }
	~SceneManager() {}

public:

	static SceneManager& instance()
	{
		// 実体化
		static SceneManager instance;
		return instance;
	}

};