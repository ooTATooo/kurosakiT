#pragma once

class CharBase :public KdGameObject
{
public:

	CharBase() { Init(); }
	virtual ~CharBase()override {}

	void Update()override;
	void PostUpdate()override;
	void Init();
	void DrawLit()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	const void SetTarget(const std::weak_ptr<KdGameObject> _target) { m_target = _target; }

protected:

	std::shared_ptr<KdModelData> m_spModel = nullptr;

	std::weak_ptr<KdGameObject> m_target;

	Math::Vector3 m_pos = Math::Vector3::Zero;
};