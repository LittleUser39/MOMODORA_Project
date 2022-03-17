#pragma once
#include "CGameObject.h"
class CKaho : public CGameObject
{
private:
	CD2DImage* m_pImg;	//캐릭터 이미지
	CD2DImage* m_pImg2;
	CD2DImage* m_pImg3;
	CD2DImage* m_pImg4;
	CD2DImage* m_pImg5; 
	CD2DImage* m_pImg6;
	CD2DImage* m_pImg7;
	CD2DImage* m_pImg8;
	CD2DImage* m_pImg9;
	CD2DImage* m_pImg10;

	const float fdealy = 0.5f; //딜레이 
	const float fcombo = 1.f; //콤보 시간 - 이안에 눌러야 연결

	bool m_rolldis;		//캐릭터 구르고 있나
	float m_rollCount;
	float m_velocity;	//캐릭터 속도
	float m_jumpforce;	//캐릭터 점프력
	float m_gravity;	//중력
	float m_HP;			//캐릭터의 체력
	
	float delay = 0; //공격 딜레이
	int combo = 0;
	
	bool m_onfloor;			//캐릭터가 바닥에 있는가
	bool m_idle;			//캐릭터가 가만히 있는가
	bool m_Fjump;			//캐릭터가 첫번째점프상태 인가
	
	bool m_dead;			//캐릭터가 죽어있는가

	bool CanAttack();		//공격할수 있다
	bool Attack();			//1번째 공격
	bool ComboAttack2();	//2번째
	bool ComboAttack3();	//3번째

	bool IsComboAttck();	//연속공격이다
public:
	CKaho();
	~CKaho();
	virtual CKaho* Clone();

	virtual void update();
	virtual void render();

	void CreateArrow();		//화살 충돌체 만듦
	void CreateHitBox();	//플레이어가 공격하면 그곳에 히트박스만듦

	virtual void OnCollision(CCollider* pOther);		//충돌중 일때
	virtual void OnCollisionEnter(CCollider* pOther);	//층돌에 들어갈때
	virtual void OnCollisionExit(CCollider* pOther);	//충돌에서 나갈때 
};

