#pragma once
#include "CGameObject.h"
class CHitBox : public CGameObject
{
	fVec2 m_fvDir;
	CGameObject* m_pOwner;

public:
	CHitBox();
	~CHitBox();
	virtual CHitBox* Clone();

	virtual void update();
	virtual void render();

	CGameObject* GetOwnerObj();
	void SetOwnerObj(CGameObject* pOwner);

	void create();
	void OnCollisionEnter(CCollider* pOther);
};

