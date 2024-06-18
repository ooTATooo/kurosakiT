#pragma once

class Enemy :public KdGameObject
{
public:
	Enemy() { Init(); }
	~Enemy()override {}

	void Update()override;
	void PostUpdate()override;
	void Init()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
private:

	KdSquarePolygon m_poly;
	Math::Vector3 m_pos;

	float m_anime = 0;

	float m_gravity = 0;

	int m_dir = 1;
	float m_goal = 0;
	float m_speed = 0;

};