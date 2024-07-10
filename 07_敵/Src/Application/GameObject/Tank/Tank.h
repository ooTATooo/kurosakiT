#pragma once

class CameraBase;

class Tank :public KdGameObject
{
public:

	Tank() { Init(); }
	~Tank()override {}

	void Update()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

	const void SetCamera(const std::weak_ptr<CameraBase>& _camera) { m_wpCamera = _camera; }

private:

	void Init()override;

	std::shared_ptr<KdModelData> m_spModel = nullptr;

	std::weak_ptr<CameraBase> m_wpCamera;

	Math::Vector3 m_pos;

	float m_angle = 0;

};