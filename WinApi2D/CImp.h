#pragma once
#include "CMonster.h"
#include "CGameObject.h"

class CD2DImage;

struct tImpInfo
{
	float fSpeed;
	float fHP;
	float fRecogRange;
	float fAttRange;
	float fAtt;
};

class CImp : public CGameObject
{
private:
	tImpInfo m_tInfo;

	CD2DImage* m_pImg;
	CD2DImage* m_pImg2;
	CD2DImage* m_pImg3;
	
	MON_STATE m_eCurState;	//현재상태
	MON_STATE m_ePerState;	//이전상태

	int          m_iCurDir;	  //현재방향
	int          m_iPreDir;	  //이전방향

public:
	CImp();
	virtual ~CImp();
	virtual CImp* Clone();

	virtual void render();
	virtual void update();

	void OnCollisionEnter(CCollider* pOther);

	void CreateDagger();

	void update_move();
	void update_state();
	void update_animation();
};