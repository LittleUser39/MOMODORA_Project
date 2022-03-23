#pragma once
#include "CGameObject.h"

class CMonster;

class CMHitBox :  public CGameObject
{
	
	CMonster* m_pOwner;

	const float m_fDelaytime = 0.5f; //µÙ∑π¿Ã 
	float m_fDelay = 0;

public:
	CMHitBox();
	~CMHitBox();
	virtual CMHitBox* Clone();

	virtual void update();
	virtual void render();

	void OnCollisionEnter(CCollider* pOther);

	CMonster* GetOwnerObj();
	void SetOwnerObj(CMonster* pOwner);
};

