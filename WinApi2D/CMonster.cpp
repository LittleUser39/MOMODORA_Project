#include "framework.h"
#include "CMonster.h"
#include "CCollider.h"

#include "CD2DImage.h"
#include "CAnimator.h"

#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CAttState.h"

#include "CGravity.h"
#include "CRigidBody.h"

CMonster::CMonster()
{
	CD2DImage* m_pImg = CResourceManager::getInst()->LoadD2DImage(L"MonsterTex", L"texture\\sMonkey_Full.png");

	m_pAI = nullptr;

	SetName(L"Monster");
	SetScale(fPoint(40, 40));
	
	CD2DImage* m_pImg2 = CResourceManager::getInst()->LoadD2DImage(L"MonsterAtt", L"texture\\sMonkeyAttack_Full1.png");
	CreateCollider();
	GetCollider()->SetScale(fPoint(40.f, 40.f));

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"sMonkey_Full", m_pImg, fPoint(0, 0), fPoint(44.f, 32.f), fPoint(44.f, 0), 0.1f, 5, true);
	GetAnimator()->Play(L"sMonkey_Full");
	GetAnimator()->CreateAnimation(L"MonkeyAtt_full",m_pImg2, fPoint(0, 0), fPoint(90.f, 48.f), fPoint(90.f, 0), 0.3f, 8, true);


	CreateGravity();
	CreateRigidBody();
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
	}
}

CMonster* CMonster::Clone()
{
	CMonster* newMonster = new CMonster;
	if (nullptr != m_pAI)
	{
		newMonster->m_pAI = new AI;
	}
	return new CMonster(*newMonster);
}

CMonster* CMonster::Create(MON_TYPE type, fPoint pos)
{
	CMonster* pMon = nullptr;

	switch (type)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CMonster;
		pMon->SetPos(pos);

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 150.f;
		info.fHP = 10.f;
		info.fSpeed = 150.f;

		AI* pAI = new AI;
		pAI->AddState(new CIdleState(MON_STATE::IDLE));
		pAI->AddState(new CTraceState(MON_STATE::TRACE));
		pAI->AddState(new CAttState(MON_STATE::ATT));
		pAI->SetCurState(MON_STATE::IDLE);
		pMon->SetMonInfo(info);
		pMon->SetAI(pAI);
	}
	break;
	case MON_TYPE::RANGE:
		break;
	default:
		break;
	}
	assert(pMon);
	return pMon;
}

void CMonster::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::getInst()->GetRenderPos(pos);

	component_render();
}

void CMonster::update()
{
	if (nullptr != GetAnimator())
		GetAnimator()->update();
	if (nullptr != m_pAI)
		m_pAI->update();
	if (nullptr != m_pAI)
	{
		if (m_mState->GetType() == MON_STATE::ATT)
		{
			GetAnimator()->Play(L"MonkeyAtt_full");
		}
	}
}



float CMonster::GetSpeed()
{
	return m_tInfo.fSpeed;
}

const tMonInfo& CMonster::GetMonInfo()
{
	return m_tInfo;
}

void CMonster::SetSpeed(float speed)
{
	m_tInfo.fSpeed = speed;
}

void CMonster::SetAI(AI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
}

void CMonster::SetMonInfo(const tMonInfo& info)
{
	m_tInfo = info;
}

void CMonster::OnCollisionEnter(CCollider* pOther)
{
	CGameObject* pOtherObj = pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player1"||pOtherObj->GetName()==L"Player_hitbox")
	{
		m_tInfo.fHP -= 1;
		if (m_tInfo.fHP <= 0)
			DeleteObj(this);
	}
}