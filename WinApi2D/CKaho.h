#pragma once
#include "CPlayer.h"
class CKaho : public CPlayer
{
private:
	CD2DImage* m_pImg;	//캐릭터 이미지
	CD2DImage* m_pImg2;
	CD2DImage* m_pImg3;

	float m_velocity;	//캐릭터 속도
	float m_jumpforce;	//캐릭터 점프력
	float m_gravity;	//중력
	float m_HP;			//캐릭터의 체력

	bool m_onfloor;		//캐릭터가 바닥에 있는가
	bool m_idle;		//캐릭터가 가만히 있는가
	bool m_Fjump;		//캐릭터가 첫번째점프상태 인가
	bool m_Djump;		//캐릭터가 두번째 점프 상태 인가
	bool m_dead;		//캐릭터가 죽어있는가

public:
	CKaho();
	~CKaho();
	virtual CKaho* Clone();

	virtual void update();
	virtual void render();

	virtual void OnCollision(CCollider* pOther);		//충돌중 일때
	virtual void OnCollisionEnter(CCollider* pOther);	//층돌에 들어갈때
	virtual void OnCollisionExit(CCollider* pOther);	//충돌에서 나갈때 
};

