#pragma once
#include "CGameObject.h"
class CHitBox : public CGameObject
{
	fVec2 m_fvDir;

public:
	CHitBox();
	~CHitBox();
	virtual CHitBox* Clone();

	virtual void update();
	virtual void render();

	void SetDir(fVec2 vec);
	void SetDir(float theta);

	void OnCollisionEnter(CCollider* pOther);
};

