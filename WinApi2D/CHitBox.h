#pragma once
#include "CGameObject.h"
class CKaho;

class CHitBox : public CGameObject
{
	CD2DImage* m_pImg;
	CD2DImage* m_pImg2;
	CD2DImage* m_pImg3;

	CKaho* m_pOwner;

	const float m_fDelaytime = 0.5f; //µÙ∑π¿Ã 
	float m_fDelay;

public:
	CHitBox();
	~CHitBox();
	virtual CHitBox* Clone();

	virtual void update();
	virtual void render();

	void update_animation();

	void OnCollisionEnter(CCollider* pOther);

	CKaho* GetOwnerObj();
	void SetOwnerObj(CKaho* pOwner);
};

