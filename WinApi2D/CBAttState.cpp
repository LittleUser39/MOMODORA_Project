#include "framework.h"
#include "CBAttState.h"
#include "CKaho.h"
#include "CFennel.h"
#include "CAnimator.h"

CBAttState::CBAttState(Boss_Pattern state) : CBState(state)
{

}

CBAttState::~CBAttState()
{

}

void CBAttState::update()
{
	CKaho* pPlayer = CKaho::GetPlayer();
	if (nullptr == pPlayer)
		return;
	fPoint fptPlayerPos = pPlayer->GetPos();
	CFennel* pBoss = GetMonster();
	fPoint fptMonsterPos = pBoss->GetPos();
	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	

	if (m_bNext)
		ChangeBossAIState(GetOwnerAI(), Boss_Pattern::IDLE);
	
	b_fDT += fDT;
	if (true)
	{
		//플레이어가 더 오른쪽에 있음 대쉬하는거
		if (0 < fvDiff.x&& m_bDash)
		{
			pBoss->GetRigidBody()->SetVelocity(fVec2(300.f, pBoss->GetRigidBody()->GetVelocity().y));
			pBoss->GetAnimator()->Play(L"FennelDashL");
			m_bDash = false;
		}
		//플레이어가 더 왼쪽에 있음
		else if (0 > fvDiff.x && m_bDash)
		{
			pBoss->GetRigidBody()->SetVelocity(fVec2(-300.f, pBoss->GetRigidBody()->GetVelocity().y));
			pBoss->GetAnimator()->Play(L"FennelDashL");
			m_bDash = false;
		}
		if (1.f <= b_fDT && m_bCanAtt)
		{
			if (0 < fvDiff.x)
			{
				pBoss->GetAnimator()->Play(L"FennelAttR");
				m_bCanAtt = false;
			}
			else if (0 > fvDiff.x && m_bCanAtt)
			{
				pBoss->GetAnimator()->Play(L"FennelAttL");
				m_bCanAtt = false;
			}
		}
		if (3.2f <= b_fDT)
		{
			if (0 < fvDiff.x && m_bFlip)
			{
				pBoss->GetAnimator()->Play(L"FennelflipR");
				pBoss->GetRigidBody()->SetVelocity(fVec2(-300.f, pBoss->GetRigidBody()->GetVelocity().y));
				m_bFlip = false;
			}
			//플레이어가 더 왼쪽에 있음
			else if (0 > fvDiff.x && m_bFlip)
			{
				pBoss->GetAnimator()->Play(L"FennelflipL");
				pBoss->GetRigidBody()->SetVelocity(fVec2(300.f, pBoss->GetRigidBody()->GetVelocity().y));
				m_bFlip = false;
			}
		}
		if (4.4f<=b_fDT)
			m_bNext = true;
	}
}

void CBAttState::Enter()
{
	m_bNext = false;
	m_bFlip = true;
	m_bDash = true;
	m_bCanAtt = true;
	b_fDT = 0;
}


void CBAttState::Exit()
{

}
