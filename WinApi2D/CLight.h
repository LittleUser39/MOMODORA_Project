#pragma once
#include "CGameObject.h"
class CLight : public CGameObject
{
private:
	CD2DImage* m_pImg;
	float m_fDelay= 0.f;
	float m_fDelaytime = 1.5f;
public:

	CLight();
	~CLight();
	virtual CLight* Clone();

	virtual void update();
	virtual void render();

	void OnCollisionEnter(CCollider* pOther);
};

