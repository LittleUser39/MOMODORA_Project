#pragma once
#include "CGameObject.h"

class CD2DImage;
class AI;
class CState;

enum class Boss_PHASE
{
	PHASE_1,
	PHASE_2,
};

class CFennel : public CGameObject
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
	CD2DImage* m_pImg11;

	float m_fHP = 100;
	float m_fAttRange = 100;

	Boss_PHASE m_CurState;

public:
	CFennel();
	virtual ~CFennel();

	virtual CFennel* Clone();

	virtual void render();
	virtual void update();

	void OnCollisionEnter(CCollider* pOther);

	void CreateHitBox();	//히트 박스 충돌체 만듦

	void SetPhase();
	void update_move();
	void update_state();
	void update_animation();

	void CreateLightning();
	void SwordStrike();
	void SwordAtt();
};


