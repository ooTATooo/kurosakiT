#pragma once

class Player :public KdGameObject
{
public:

	Player() { Init(); }
	~Player()override {}

	void Update()override;
	void Init()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

private:

	KdSquarePolygon m_poly;
	Math::Vector3 m_pos;

	float m_anime = 0;
};