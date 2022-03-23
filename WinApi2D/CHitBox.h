#pragma once
#include "CGameObject.h"

class CHitBox : public CGameObject
{
	CD2DImage* m_pImg;

	const float m_fDelaytime = 0.5f; //µÙ∑π¿Ã 
	float m_fDelay;

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

