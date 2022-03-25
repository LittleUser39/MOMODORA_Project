#include "framework.h"
#include "CFennel.h"
#include "CKaho.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CCollider.h"

#include "CGravity.h"
#include "CRigidBody.h"

CFennel::CFennel()
{
	SetName(L"Fennel");
	SetScale(fPoint(100.f, 100.f));
	
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"FennelIdle",L"texture\\sFennelIdle_Full.png");
	m_pImg2 = CResourceManager::getInst()->LoadD2DImage(L"FenneAtt", L"texture\\sFennelAtt_Full.png");
	m_CurState = Boss_Pattern::IDEL;
	
	CreateCollider();
	GetCollider()->SetScale(fPoint(60.f, 75.f));

	//자른 크기 55,55,100,100
	//공격 자른크기 100,55,60,105
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"FennelIdle", m_pImg, fPoint(0,0), fPoint(55.f,55.f), fPoint(55.f,0), 0.1f, 4, true);
	GetAnimator()->CreateAnimation(L"FennelAtt", m_pImg2, fPoint(0, 0), fPoint(102.f, 66.f), fPoint(102.f, 0), 0.1f, 22, true);
	
	CreateGravity();
	CreateRigidBody();
}

CFennel::~CFennel()
{

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
	update_move();
	update_state();
	update_animation();

	GetAnimator()->update();
}

void CFennel::OnCollisionEnter(CCollider * pOther)
{

}

void CFennel::CreateHitBox()
{

}

void CFennel::SetPhase()
{
	
}

void CFennel::update_move()
{ 
	//todo 플레이어 방향으로 대쉬하는거 
	CKaho* pPlayer = CKaho::GetPlayer();
	fPoint fptPlayerPos = pPlayer->GetPos();

	fPoint fptBossPos = GetPos();

	fVec2 fvDiff = fptPlayerPos - fptBossPos;
	
	
	if (fvDiff.x > m_fAttRange)
	{
		m_CurState = Boss_Pattern::SWORDATTACK;
	}
	else if (fvDiff.x <= m_fAttRange)
	{
		m_CurState = Boss_Pattern::IDEL;
	}
	
}

void CFennel::update_state()
{
	if (50 >= m_fHP)
	{
		Boss_PHASE::PHASE_2;
	}
}

void CFennel::update_animation()
{
	switch (m_CurState)
	{
	case Boss_Pattern::IDEL:
	{
		GetAnimator()->Play(L"FennelIdle");
	}
		break;
	case Boss_Pattern::SWORDATTACK:
	{
		GetAnimator()->Play(L"FennelAtt");
	}
		break;
	case Boss_Pattern::LIGTHNING:
	{

	}
		break;
	case Boss_Pattern::SWORDSTRIKE:
	{

	}
		break;
	}
	
}

void CFennel::CreateLightning()
{
}

void CFennel::SwordStrike()
{
}

void CFennel::SwordAtt()
{
}
