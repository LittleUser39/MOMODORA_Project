#pragma once
#include "CGameObject.h"

class CHitBox;

enum class PLAYER_STATE
{
	IDLE,
	WALK,
	BRAKE,
	CROUCH,
	ROLL,
	BOW,
	CROUCHBOW,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	JUMP,
	DEAD,
	END
};

class CKaho : public CGameObject
{
private:
	static CKaho* instance; //하나만 있는 플레이어

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
	CD2DImage* m_pImg11;

	PLAYER_STATE m_eCurState; //캐릭터 현재상태
	PLAYER_STATE m_ePreState; //캐릭터 이전상태
	
	int          m_iCurDir;	  //현재방향
	int          m_iPreDir;	  //이전방향

	float m_fPMAXHP;
	float m_fPHP;

	const float m_fDelaytime = 0.5f; //딜레이 
	const float m_fCombotime = 1.f; //콤보 시간 - 이안에 눌러야 연결

	float m_fRollCoolTime = 1.f;
	float m_fRollTime = 0;

	float m_fDelay = 0; //공격 딜레이
	int	  m_iCombo = 0;
	
	bool m_onfloor;			//캐릭터가 바닥에 있는가
	bool m_bAttacking;		//캐릭터가 공격중 인가
	bool m_bJump;			//점프상태
	bool m_bDead;			//캐릭터가 죽어있는가
	bool m_bCrouch;			//캐릭터가 웅크린 상태 인가
	bool m_bBow;

public:
	CKaho();
	~CKaho();
	virtual CKaho* Clone();

	void update_move();
	void update_state();
	void update_animation();

	virtual void update();
	virtual void render();

	float GetDirect();

	void CreateArrow();		//화살 충돌체 만듦
	void CreateHitBox();	//히트 박스 충돌체 만듦
	float GetHP();
	virtual void OnCollision(CCollider* pOther);		//충돌중 일때
	virtual void OnCollisionEnter(CCollider* pOther);	//층돌에 들어갈때
	virtual void OnCollisionExit(CCollider* pOther);	//충돌에서 나갈때 

	const int GetAttCount();

	virtual void RegisterPlayer();
	static CKaho* GetPlayer();	// 게임 내에 하나만 있는 플레이어 객체 확인(임의로 싱글톤 선언)
	void RenderPlayerInfo();
};

