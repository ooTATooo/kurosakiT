#pragma once

class Reticle :public KdGameObject
{
public:

	Reticle() { Init(); }
	virtual ~Reticle()override {}

	void Init()override;
	void DrawSprite()override;

private:

	std::shared_ptr<KdTexture> m_spTex = nullptr;
};