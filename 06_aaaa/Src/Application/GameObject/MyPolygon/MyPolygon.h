#pragma once

class MyPolygon :public KdGameObject
{
public:

	MyPolygon() {}
	~MyPolygon()override {}

	void Init()override;
	void DrawLit()override;
	void Update()override;

private:

	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;

};