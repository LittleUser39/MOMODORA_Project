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
	
	MON_STATE m_eCurState;	//�������
	MON_STATE m_ePerState;	//��������

	int          m_iCurDir;	  //�������
	int          m_iPreDir;	  //��������

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