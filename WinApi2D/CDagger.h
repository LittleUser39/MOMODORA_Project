#pragma once
#include "CGameObject.h"
class CDagger : public CGameObject
{

private:
	fVec2 m_fvDir;
	float m_fVelocity = 400.f;
	CD2DImage* m_pImg;

public:
	CDagger();
	~CDagger();
	virtual CDagger* Clone();

	virtual void update();
	virtual void render();

	void SetDir(fVec2 vec);
	void SetDir(float theta);

	void OnCollisionEnter(CCollider* pOther);
};

