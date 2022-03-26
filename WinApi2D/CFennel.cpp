#include "framework.h"
#include "CFennel.h"
#include "CKaho.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CCollider.h"
#include "BossAI.h"
#include "CBState.h"
#include "CGravity.h"
#include "CRigidBody.h"

#include "CBIdleState.h"
#include "CBAttState.h"
#include "CBLightning.h"
#include "CLight.h"
CFennel::CFennel()
{
	SetName(L"Fennel");
	SetScale(fPoint(70.f, 70.f));
	m_pAI = nullptr;

	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"FennelIdle",L"texture\\sFennelIdle_Full.png");
	m_pImg2 = CResourceManager::getInst()->LoadD2DImage(L"FenneAtt", L"texture\\sFennelAtt_Full.png");
	m_pImg3 = CResourceManager::getInst()->LoadD2DImage(L"FenneDash", L"texture\\sFennelDash_0.png");

	m_bBack = true;
	m_bDash = true;
	
	
	CreateCollider();
	GetCollider()->SetScale(fPoint(60.f, 75.f));

	//자른 크기 55,55,100,100
	//공격 자른크기 100,55,60,105
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"FennelIdleL", m_pImg, fPoint(0,0), fPoint(55.f,55.f), fPoint(55.f,0), 0.1f, 4, false);
	GetAnimator()->CreateAnimation(L"FennelIdleR", m_pImg, fPoint(0, 0), fPoint(55.f, 55.f), fPoint(55.f, 0), 0.1f, 4, false, true);
	
	GetAnimator()->CreateAnimation(L"FennelDashL", m_pImg3, fPoint(0, 0), fPoint(55.f, 55.f), fPoint(55.f, 0), 0.1f, 1, false);
	GetAnimator()->CreateAnimation(L"FennelDashR", m_pImg3, fPoint(0, 0), fPoint(55.f, 55.f), fPoint(55.f, 0), 0.1f, 1, false, true);

	GetAnimator()->CreateAnimation(L"FennelAttL", m_pImg2, fPoint(0, 0), fPoint(102.f, 66.f), fPoint(102.f, 0), 0.1f, 22, false);
	GetAnimator()->CreateAnimation(L"FennelAttR", m_pImg2, fPoint(0, 0), fPoint(102.f, 66.f), fPoint(102.f, 0), 0.1f, 22, false , true);

	GetAnimator()->Play(L"FennelIdleL");

	CreateGravity();
	CreateRigidBody();
}

CFennel::~CFennel()
{
	if (nullptr != m_pAI)
	{
		delete m_pAI;
	}
}

CFennel * CFennel::Clone()
{
	return nullptr;
}

void CFennel::render()
{
	component_render();
}

void CFennel::update()
{
	if (nullptr != GetAnimator())
		GetAnimator()->update();
	if (nullptr != m_pAI)
		m_pAI->update();
	
	m_fDelay += fDT;
	if (5.f <= m_fDelay)
	{
		CreateLighting();
		m_fDelay = 0;
	}
}

void CFennel::OnCollisionEnter(CCollider * pOther)
{

}

void CFennel::CreateHitBox()
{

}

CFennel* CFennel::Create(Boss_PHASE type, fPoint pos)
{
	CFennel* pBoss = nullptr;

	switch (type)
	{
	case Boss_PHASE::PHASE_1:
	{
		pBoss = new CFennel;
		pBoss->SetPos(pos);

		tBossInfo info = {};
		info.fAttRange = 100;
		info.fHP = 100;
		info.fMaxHP = 100;
		

		BossAI* pAI = new BossAI;
		pAI->AddState(new CBIdleState(Boss_Pattern::IDLE));
		pAI->AddState(new CBAttState(Boss_Pattern::SWORDATTACK));
		pAI->AddState(new CBLightning(Boss_Pattern::LIGTHNING));
		pAI->SetCurState(Boss_Pattern::IDLE);
		pBoss->SetMonInfo(info);
		pBoss->SetAI(pAI);
	}
	break;
	default:
		break;
	}
	assert(pBoss);
	return pBoss;
}

void CFennel::SetMonInfo(const tBossInfo& info)
{
	m_tInfo = info;
}

const tBossInfo& CFennel::GetMonInfo()
{
	return m_tInfo;
}

void CFennel::SetAI(BossAI* ai)
{
	m_pAI = ai;
	m_pAI->m_pOwner = this;
}
//
//void CFennel::update_state()
//{
//	//CKaho* pPlayer = CKaho::GetPlayer();
//	//fPoint fptPlayerPos = pPlayer->GetPos();
//
//	//fPoint fptBossPos = GetPos();
//
//	//// 플레이어 위치 - 보스 위치
//	//fVec2 fvDiff = fptPlayerPos - fptBossPos;
//	//float fLen = fvDiff.Length();
//	//
//	//if (50 >= m_fHP)
//	//{
//	//	Boss_PHASE::PHASE_2;
//	//}
//	//if (fLen <= m_fAttRange)
//	//{
//	//	m_CurState = Boss_Pattern::SWORDATTACK;
//	//	
//	//}
//	//else if (fLen > m_fAttRange)
//	//{
//	//	m_CurState = Boss_Pattern::DASH;
//	//}
//
//}
//
//void CFennel::SwordStrike()
//{
//	//대쉬 후 2번 연속 공격 , 일정범위안 이면 그냥 2번공격
//	Dash();
//
//	if (0.f == GetRigidBody()->GetSpeed())
//	{
//		GetAnimator()->Play(L"FennelAttL");
//		m_bDash = true;
//	}
//	
//	
//}
//
void CFennel::Dash()
{
	CKaho* pPlayer = CKaho::GetPlayer();
	fPoint fptPlayerPos = pPlayer->GetPos();

	fPoint fptBossPos = GetPos();

	// 플레이어 위치 - 보스 위치
	fVec2 fvDiff = fptPlayerPos - fptBossPos;

	//플레이어가 더 오른쪽에 있음
	if (0 < fvDiff.x && true == m_bDash)
	{
		GetRigidBody()->SetVelocity(fVec2(300.f, GetRigidBody()->GetVelocity().y));
		GetAnimator()->Play(L"FennelDashL");
		m_bDash = false;
	}
	//플레이어가 더 왼쪽에 있음
	else if (0 > fvDiff.x && m_bDash)
	{
		GetRigidBody()->SetVelocity(fVec2(-300.f, GetRigidBody()->GetVelocity().y));
		GetAnimator()->Play(L"FennelDashL");
		m_bDash = false;
	}

}

void CFennel::Back()
{
	CKaho* pPlayer = CKaho::GetPlayer();
	fPoint fptPlayerPos = pPlayer->GetPos();

	fPoint fptBossPos = GetPos();

	// 플레이어 위치 - 보스 위치
	fVec2 fvDiff = fptPlayerPos - fptBossPos;

	//플레이어가 더 오른쪽에 있음
	if (0 < fvDiff.x && m_bBack)
	{
		GetRigidBody()->SetVelocity(fVec2(-300.f, GetRigidBody()->GetVelocity().y));
		GetAnimator()->Play(L"FennelDashR");
		m_bBack = false;
	}
	//플레이어가 더 왼쪽에 있음
	else if (0 > fvDiff.x && m_bBack)
	{
		GetRigidBody()->SetVelocity(fVec2(300.f, GetRigidBody()->GetVelocity().y));
		GetAnimator()->Play(L"FennelDashR");
		m_bBack = false;
	}
}

void CFennel::CreateLighting()
{
	CKaho* pPlayer = CKaho::GetPlayer();
	fPoint fptPlayerPos = pPlayer->GetPos();


	
	CLight* mLight = new CLight;
	mLight->SetPos(fptPlayerPos);
	CreateObj(mLight, GROUP_GAMEOBJ::MISSILE_MONSTER);
	CLight* mLight2 = mLight->Clone();
	mLight->SetPos(mLight->GetPos() + fPoint(20.f, 0));
	CreateObj(mLight2, GROUP_GAMEOBJ::MISSILE_MONSTER);
}
