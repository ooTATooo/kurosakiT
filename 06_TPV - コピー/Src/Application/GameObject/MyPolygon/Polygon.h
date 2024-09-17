#pragma once

class Polygon :public KdGameObject
{
public:

	Polygon() {}
	~Polygon()override {}

	void Init()override;
	void DrawLit()override;

private:

	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;

};