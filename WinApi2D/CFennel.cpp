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
	m_CurState = Boss_PHASE::PHASE_1;
	
	CreateCollider();
	GetCollider()->SetScale(fPoint(60.f, 75.f));

	//자른 크기 55,55,100,100
	//공격 자른크기 100,55,60,105
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"FennelIdle", m_pImg, fPoint(0,0), fPoint(55.f,55.f), fPoint(55.f,0), 0.1f, 4, true);
	GetAnimator()->CreateAnimation(L"FennelAtt", m_pImg2, fPoint(0, 0), fPoint(100.f, 55.f), fPoint(100.f, 0), 0.1f, 22, true);
	
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
	float fLen = fvDiff.Length();
	
	if (fLen > m_fAttRange)
	{
	/*	GetRigidBody()->SetVelocity(fVec2(-500.f, GetRigidBody()->GetVelocity().y));
	*/}
	else if (fLen <= m_fAttRange)
	{
		GetAnimator()->Play(L"FennelAtt");
	}
	
}

void CFennel::update_state()
{
	if (50 >= m_fHP)
	{
		m_CurState = Boss_PHASE::PHASE_2;
	}
}

void CFennel::update_animation()
{
	GetAnimator()->Play(L"FennelIdle");
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
