#pragma once

class Bullet :public KdGameObject
{
public:

	Bullet() { Init(); }
	~Bullet()override {}

	void Update()override;
	void Init()override;
	void DrawLit()override;
	void DrawBright()override;

	void SetParam(Math::Vector3 _pos, Math::Vector3 _dir, float _speed = 1.0f, int _lifeSpan = 1000);

private:

	std::shared_ptr<KdModelData> m_spModel = nullptr;

	Math::Vector3 m_pos;

	Math::Vector3 m_dir;

	float m_speed = 0;

	int m_lifeSpan = 0;
};