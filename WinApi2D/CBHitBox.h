#pragma once
#include "CGameObject.h"

class CFennel;

class CBHitBox : public CGameObject
{
	CFennel* m_pOwner;

	const float m_fDelaytime = 0.5f; //µÙ∑π¿Ã 
	float m_fDelay = 0;

	public:
	CBHitBox();
	~CBHitBox();
	virtual CBHitBox* Clone();

	virtual void update();
	virtual void render();

	void OnCollisionEnter(CCollider* pOther);

	CFennel* GetOwnerObj();
	void SetOwnerObj(CFennel* pOwner);
};

