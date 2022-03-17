#pragma once
#include "CGameObject.h"

enum class PLAYER_STATE
{
	IDLE,
	WALK,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	DEAD,
	END
};


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

	PLAYER_STATE m_eCurState; //캐릭터 현재상태
	PLAYER_STATE m_ePreState; //캐릭터 이전상태
	int          m_iCurDir;	  //현재방향
	int          m_iPreDir;	  //이전방향
		
	const float fdealy = 0.5f; //딜레이 
	const float fcombo = 1.5f; //콤보 시간 - 이안에 눌러야 연결

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

	void update_state();	 //상태 업데이트 - 이걸 이용해서 애니메이션 전환
	void update_move();		 //움직임 업데이트
	void update_animation(); //상태에 따른 애니메이션 업데이트

	void CreateArrow();		//화살 충돌체 만듦
	void CreateHitBox();	//플레이어가 공격하면 그곳에 히트박스만듦

	virtual void OnCollision(CCollider* pOther);		//충돌중 일때
	virtual void OnCollisionEnter(CCollider* pOther);	//층돌에 들어갈때
	virtual void OnCollisionExit(CCollider* pOther);	//충돌에서 나갈때 
};

