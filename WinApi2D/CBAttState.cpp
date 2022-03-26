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
	b_fDT += fDT;

	if (false)
		ChangeBossAIState(GetOwnerAI(), Boss_Pattern::IDLE);

	if (m_bCanAtt)
	{
		pBoss->Dash();
		if (1.f <= b_fDT)
		{
			if (0 < fvDiff.x)
			{
				pBoss->GetAnimator()->Play(L"FennelAttR");
			}
			else if (0 > fvDiff.x)
			{
				pBoss->GetAnimator()->Play(L"FennelAttL");
			}
		}
		if (3.f <= b_fDT)
		{
			pBoss->Back();
			m_bCanAtt = false;
		}
	}
}

void CBAttState::Enter()
{
	m_bCanAtt = true;
	b_fDT = 0;
}


void CBAttState::Exit()
{

}
