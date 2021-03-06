#pragma once
#include "CGameObject.h"

class CD2DImage;
class AI;
class CState;

struct tMonInfo
{
	float fSpeed;
	float fHP;
	float fRecogRange;
	float fAttRange;
	float fAtt;
};

enum class MON_TYPE
{
	NORMAL,
	RANGE,

	SIZE,
};

class CMonster : public CGameObject
{
private:
	tMonInfo m_tInfo;
	AI* m_pAI;
	CState* m_mState;

public:
	CMonster();
	virtual ~CMonster();
	virtual CMonster* Clone();

	static CMonster* Create(MON_TYPE type, fPoint pos);

	virtual void render();
	virtual void update();

	float GetSpeed();
	

	void SetSpeed(float speed);
	void SetAI(AI* ai);

	void SetMonInfo(const tMonInfo& info);
	const tMonInfo& GetMonInfo();

	void OnCollisionEnter(CCollider* pOther);

	void CreateHitBox();	//히트 박스 충돌체 만듦
};