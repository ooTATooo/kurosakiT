#pragma once

class Tank :public KdGameObject
{
public:

	Tank() { Init(); }
	~Tank()override {}

	void Update()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

private:

	void Init()override;

	std::shared_ptr<KdModelData> m_spModel = nullptr;

};