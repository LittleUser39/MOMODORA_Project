#include "framework.h"
#include "CBIdleState.h"
#include "framework.h"
#include "CKaho.h"
#include "CAnimator.h"
#include "CFennel.h"

CBIdleState::CBIdleState(Boss_Pattern state)
	: CBState(state)
{
}

CBIdleState::~CBIdleState()
{
}

void CBIdleState::update()
{
	CKaho* pPlayer = CKaho::GetPlayer();
	if (nullptr == pPlayer)
		return;
	fPoint fptPlayerPos = pPlayer->GetPos();
	CFennel* pBoss = GetMonster();
	fPoint fptMonsterPos = pBoss->GetPos();
	fVec2 fvDiff = fptPlayerPos - fptMonsterPos;
	m_bfDT += fDT;
	int Pattern = rand() % 2 ;
	if (2.f <= m_bfDT)
	{
		if (1 == Pattern)
		{
			ChangeBossAIState(GetOwnerAI(), Boss_Pattern::SWORDATTACK);
		}
		/*else if (1 == Pattern)
		{
			ChangeBossAIState(GetOwnerAI(), Boss_Pattern::LIGTHNING);
		}*/
	}
	if (0 < fvDiff.x)
		pBoss->GetAnimator()->Play(L"FennelIdleR");
	else if (0 > fvDiff.x)
		pBoss->GetAnimator()->Play(L"FennelIdleL");
}

void CBIdleState::Enter()
{
	m_bfDT = 0;
}

void CBIdleState::Exit()
{

}
