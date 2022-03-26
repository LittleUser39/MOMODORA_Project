#pragma once
#include "CGameObject.h"

class CD2DImage;
class BossAI;
class CBState;

struct tBossInfo
{
	float fHP;
	float fMaxHP;
	float fAttRange;
	
};

enum class Boss_PHASE
{
	PHASE_1,
	PHASE_2,
};

class CFennel : public CGameObject
{
	
private:
	tBossInfo m_tInfo;
	BossAI* m_pAI;
	CBState* m_mState;

	CD2DImage* m_pImg;	//ĳ���� �̹���
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

	

	const float m_fDelaytime = 0.5f; //������ 

	float m_fRollCoolTime = 1.f;
	float m_fRollTime = 0;

	float m_fDelay = 0; //���� ������

	bool m_bDash;
	bool m_bBack;
public:
	CFennel();
	virtual ~CFennel();

	virtual CFennel* Clone();

	virtual void render();
	virtual void update();

	void OnCollisionEnter(CCollider* pOther);

	void CreateHitBox();	//��Ʈ �ڽ� �浹ü ����

	static CFennel* Create(Boss_PHASE type, fPoint pos);

	void SetMonInfo(const tBossInfo& info);
	const tBossInfo& GetMonInfo();

	void SetAI(BossAI* ai);

	void Dash();
	void Back();
	void CreateLighting();
};


